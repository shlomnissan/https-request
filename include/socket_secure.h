// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "socket.h"

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

namespace Net {
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

    struct X509_deleter {
        auto operator()(X509* cert) const {
            X509_free(cert);
        }
    };

    using SSL_CTX_ptr = std::unique_ptr<SSL_CTX, SSL_CTX_deleter>;
    using SSL_ptr = std::unique_ptr<SSL, SSL_deleter>;
    using X509_ptr = std::unique_ptr<X509, X509_deleter>;

    class SocketSecure : public Socket {
    public:
        explicit SocketSecure(Endpoint endpoint);

        void connect(std::string_view host) override;
        ssize_t send(std::string_view buffer, milliseconds timeout) const override;
        ssize_t recv(uint8_t* buffer, milliseconds timeout) const override;

    private:
        SSL_ptr ssl_ {nullptr};
        SSL_CTX_ptr ctx_ {nullptr};
    };

    struct SocketSecureError : public std::runtime_error {
        using runtime_error::runtime_error;
    };
}