// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#if defined(_WIN32)

#include <system_error>

#include "winsock.h"
#include "sock_defs.h"

namespace Net {
    WinSock::WinSock() {
        WSADATA wsa_data;
        const auto error = WSAStartup(MAKEWORD(2, 2), &wsa_data);

        if (error != 0) {
            throw std::system_error{error, std::system_category(), "WSAStartup failed"};
        }

        if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
            WSACleanup();
            throw std::runtime_error{"Invalid WinSock version"};
        }
    }

    WinSock::~WinSock() {
        WSACleanup();
    }
}

#endif