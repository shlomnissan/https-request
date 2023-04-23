// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#if defined(_WIN32)

namespace Net {
    class WinSock {
    public:
        WinSock();

        // delete copy/move constructors and assignment operators
        WinSock(const WinSock &rhs) = delete;
        WinSock(WinSock &&rhs) = delete;
        WinSock &operator=(const WinSock &) = delete;
        WinSock &operator=(WinSock &&) = delete;

        ~WinSock();
    };
}

#endif