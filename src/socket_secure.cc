// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "socket_secure.h"

namespace Net {
    SocketSecure::SocketSecure(Endpoint endpoint)
      : Socket(std::move(endpoint)) {
        // Initialize OpenSSL
        SSL_library_init();
        SSL_load_error_strings();

        // Create a new OpenSSL context
        auto context = SSL_CTX_new(TLS_client_method());
        if (context == nullptr) {
            throw SocketSecureError {
                "Failed to initialize OpenSSL context"
            };
        }
        ctx_.reset(context);

        // Load trusted CAs
        if (!SSL_CTX_load_verify_locations(context, "ca-bundle.crt", 0)) {
            throw SocketSecureError {
                "Failed to load trusted certificate authorities"
            };
        }

        #if (OPENSSL_VERSION_NUMBER < 0x0090600fL)
            SSL_CTX_set_verify_depth(ctx_,1);
        #endif
    }

    void SocketSecure::connect() {
        Socket::connect();

        ssl_.reset(SSL_new(ctx_.get()));
        auto sbio = BIO_new_socket(fd_socket_, BIO_NOCLOSE);
        SSL_set_bio(ssl_.get(), sbio, sbio);

        // Perform SSL handshake
        if (SSL_connect(ssl_.get()) <= 0) {
            throw SocketSecureError {
                "Failed to connect SSL socket"
            };
        }

        // TODO: verify certificate
    }

    ssize_t SocketSecure::send(std::string_view buffer, milliseconds timeout) const {
        wait(EventType::ToWrite, timeout);
        return SSL_write(ssl_.get(), buffer.data(), static_cast<int>(buffer.size()));
    }

    ssize_t SocketSecure::recv(uint8_t *buffer, milliseconds timeout) const {
        wait(EventType::ToRead, timeout);
        return SSL_read(ssl_.get(), reinterpret_cast<char*>(buffer), BUFSIZ);
    }
}