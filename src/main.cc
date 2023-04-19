// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <memory>
#include <fmt/format.h>
#include <iostream>

#include "socket.h"
#include "socket_secure.h"
#include "url.h"

using namespace std::chrono_literals;

auto socket_factory(const Net::URL& url) -> std::unique_ptr<Net::Socket> {
    Net::Endpoint endpoint {url.host(), url.port()};
    if (url.scheme() == "https") {
        return std::make_unique<Net::SocketSecure>(std::move(endpoint));
    }
    return std::make_unique<Net::Socket>(std::move(endpoint));
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: https_request https://example.com\n";
        return 1;
    }

    Net::URL url {argv[1]};
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

    socket->send(request.data(), 0s);
    uint8_t temp_buffer[BUFSIZ];
    while (true) {
        auto size = socket->recv(temp_buffer, 0s);
        if (size == 0) {
            break;
        }
        std::cout << temp_buffer << '\n';
    }

    return 0;
}
