// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <chrono>
#include <iostream>
#include <string>
#include <string_view>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "socket.hpp"

using namespace std::chrono_literals;

auto init_openssl() {
    std::cout << "Initializing OpenSSL\n";
    std::cout << OpenSSL_version(SSLEAY_VERSION) << '\n';
    // initialize SSL library by registering algorithms
    SSL_library_init();
    // adds all algorithms to the table (digests and ciphers).
    OpenSSL_add_all_algorithms();
    // registers the error strings for all libcrypto and libssl functions.
    SSL_load_error_strings();
}

auto print_ssl_certificate(SSL* ssl) {
    std::cout << "\nPrint SSL certificate details\n";
    X509 *cert = SSL_get_peer_certificate(ssl);
    if (!cert) {
        std::cerr << "SSL_get_peer_certificate() failed.\n";
        return 1;
    }

    char *tmp;
    if ((tmp = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0))) {
        std::cout << "Subject: " << tmp << '\n';
        OPENSSL_free(tmp);
    }

    if ((tmp = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0))) {
        std::cout << "Issuer: " << tmp << "\n\n";
        OPENSSL_free(tmp);
    }

    X509_free(cert);

    return 0;
}

struct SSL_CTX_deleter {
    auto operator()(SSL_CTX* ctx) const {
        SSL_CTX_free(ctx);
    }
};

struct SSL_deleter {
    auto operator()(SSL* ssl) const {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }
};

using SSL_ctx_ptr = std::unique_ptr<SSL_CTX, SSL_CTX_deleter>;
using SSL_ptr = std::unique_ptr<SSL, SSL_deleter>;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: https_request https://example.com\n";
        return 1;
    }


    std::string_view hostname = argv[1];

    init_openssl();

    Net::Socket socket {{hostname, "443"}};
    socket.connect();

    // An SSLContext is used to set various options regarding certificates,
    // algorithms, verification, session caching, etc. The SSLContext is used to
    // create an SSLSocket. All attributes must be set before creating an
    // SSLSocket as the SSLContext will be frozen afterward.
    SSL_ctx_ptr ctx {SSL_CTX_new(TLS_client_method())};
    if (ctx == nullptr) {
        std::cerr << "SSL_CTX_new() failed.\n";
        return 1;
    }

    // Load CA certificates for verification.
    if (!SSL_CTX_load_verify_locations(ctx.get(), "ca-bundle.crt", 0)) {
        std::cerr << "SSL_CTX_load_verify_locations() failed.\n";
        ERR_print_errors_fp(stderr);
        return 1;
    }

    std::string request {
        "GET / HTTP/1.1\r\n"
        "Host: www.betamark.com\r\n"
        "User-Agent: express/0.1\r\n"
        "Connection: close\r\n"
        "\r\n"
    };

    SSL_ptr ssl {SSL_new(ctx.get())};
    if (!SSL_set_tlsext_host_name(ssl.get(), hostname.data())) {
        std::cerr << "SSL_set_tlsext_host_name() failed.\n";
        ERR_print_errors_fp(stderr);
        return 1;
    }

    SSL_set_fd(ssl.get(), socket.get());
    if (SSL_connect(ssl.get()) == -1) {
        std::cerr << "SSL_connect() failed.\n";
        ERR_print_errors_fp(stderr);
        return 1;
    }

    print_ssl_certificate(ssl.get());

    auto vp = SSL_get_verify_result(ssl.get());
    if (vp == X509_V_OK) {
        std::cout << "-- Certificate is verified\n\n";
    } else {
        std::cout << "-- Couldn't verify SSL certificate\n\n";
        return 1;
    }

    SSL_write(ssl.get(), request.c_str(), request.size());
    uint8_t temp_buffer[BUFSIZ];
    while (true) {
        auto size = SSL_read(ssl.get(), temp_buffer, BUFSIZ);
        if (size == 0) {
            break;
        }
        std::cout << temp_buffer << '\n';
    }

    return 0;
}
