// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <memory>
#include <fmt/format.h>

#include "socket.h"
#include "socket_secure.h"
#include "url.h"

using namespace std::chrono_literals;
using namespace Net;

auto socket_factory(const URL& url) -> std::unique_ptr<Socket>;

auto main(int argc, char *argv[]) -> int {
    if (argc < 2) {
        std::cerr << "Usage: https_request https://example.com\n";
        return 1;
    }

    URL url {argv[1]};
    auto socket = socket_factory(url);
    socket->connect();

    auto request{
        fmt::format(
            "GET / HTTP/1.1\r\n"
            "Host: {}\r\n"
            "User-Agent: https-request/0.1\r\n"
            "Connection: close\r\n"
            "\r\n",
            url.host()
        )
    };

    socket->send(request, 0s);
    uint8_t temp_buffer[BUFSIZ];
    while (true) {
        if (socket->recv(temp_buffer, 0s) <= 0) {
            break;
        }
        std::cout << temp_buffer << '\n';
    }

    return 0;
}

auto socket_factory(const URL& url) -> std::unique_ptr<Socket> {
    Endpoint endpoint {url.host(), url.port()};
    if (url.scheme() == "https") {
        return std::make_unique<SocketSecure>(std::move(endpoint));
    }
    return std::make_unique<Socket>(std::move(endpoint));
}