// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once


#include <chrono>

#include "endpoint.h"
#include "sock_defs.h"

namespace Net {
    using namespace std::chrono;

    enum class EventType {ToRead, ToWrite};

    class Socket {
    public:
        explicit Socket(Endpoint endpoint);

        // deletes copy/move constructor and assignment
        Socket(Socket&& rhs) noexcept = delete;
        auto operator=(Socket&& rhs) noexcept -> Socket& = delete;
        Socket(const Socket&) = delete;
        auto operator=(const Socket&) -> Socket& = delete;

        virtual auto connect() -> void;
        virtual auto send(std::string_view buffer, milliseconds timeout) const -> ssize_t;
        virtual auto recv(uint8_t* buffer, milliseconds timeout) const -> ssize_t;

        auto sendAll(std::string_view buffer, milliseconds timeout) const -> void;

        [[nodiscard]] SOCKET get() const { return fd_socket_; };

        virtual ~Socket();

    protected:
        SOCKET fd_socket_ = INVALID_SOCKET;
        Endpoint endpoint_;

        auto wait(EventType event, milliseconds timeout) const -> void;
    };

    struct SocketError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
}