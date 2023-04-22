// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once


#include <chrono>

#include "endpoint.h"

#if defined(_WIN32)
#include <winsock2.h>
#include <BaseTsd.h>

using ssize_t = SSIZE_T;

#define SYS_EINTR WSAEINTR
#define CLOSE(s) closesocket(s)
#define ERRNO() (WSAGetLastError())
#else
#include <cerrno>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

using SOCKET = int;
constexpr auto INVALID_SOCKET = -1;

#define SYS_EINTR EINTR
#define CLOSE(s) close(s)
#define ERRNO() (errno)
#endif

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

        virtual auto connect(std::string_view host) -> void;
        virtual auto send(std::string_view buffer, milliseconds timeout) const -> ssize_t;
        virtual auto recv(uint8_t* buffer, milliseconds timeout) const -> ssize_t;

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