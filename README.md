# 🌍 https-request
This is a simple tool written in modern C++. It makes HTTP/S requests to a given host and prints the output.

[![Ubuntu](https://github.com/shlomnissan/https-request/workflows/Ubuntu/badge.svg)](https://github.com/shlomnissan/https-request/actions/workflows/ubuntu.yml)
[![MacOS](https://github.com/shlomnissan/https-request/workflows/MacOS/badge.svg)](https://github.com/shlomnissan/https-request/actions/workflows/macos.yml)
[![Windows](https://github.com/shlomnissan/https-request/workflows/Windows/badge.svg)](https://github.com/shlomnissan/https-request/actions/workflows/windows.yml)

- The goal of this project is to experiment with HTTP clients and OpenSSL. It is not a full-featured HTTP client. For a complete production-grade HTTP client library in C++, check out [express-client](https://github.com/shlomnissan/express-client).
- If you find this project informative or useful, please ⭐️ this repository to show your support.

## Features
- A command-line application
- Supports both HTTP and HTTPS protocols
- Written in modern C++
- Cross-platform

## HTTPS and certificate verification
Every operating system provides a list of trusted Certificate Authorities (CAs) that can be used to verify SSL certificates. However, there is no general way to import these lists.

Mozilla maintains its own trusted certificate authority (CA) store, which is frequently used by HTTP clients. [curl](https://curl.se/) has developed tools to extract these certificates from Firefox and convert them to a file containing the CAs' digital signatures suitable for certificate verification. This file can be downloaded directly from their servers at https://curl.se/docs/caextract.html.

The **https-request** executable requires a trusted CAs file named `ca-bundle.crt` to be placed in the same directory. This project includes a CMake option called `FETCH_TRUSTED_CA` (enabled by default) that downloads the Mozilla CA store into the build's binary directory. If you prefer to use a different store, turn off this option and place your own `ca-bundle.crt` file along with the **https-request** executable.

## Build
The steps below have been tested on Linux, MacOS, and Windows:

**1. Install dependencies**

Please make sure that the following dependencies are installed on your system:
- CMake (minimum version 3.22)
- OpenSSL

**2. Clone the repository**
```
$ git clone https://github.com/shlomnissan/https-request.git
```
**3. Generate build files for your environment**
```
$ cd https-request
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
```
To generate a build for the Release version, specify `-DCMAKE_BUILD_TYPE=Release` instead.

**4. Build the tool**
```
cmake --build .
```
Alternatively, you can build the project using your default build system directly.

## Usage

This command-line application accepts a single argument: the hostname of the website to which you want to connect.
Only the HTTP and HTTPS URL schemes are supported.
```
$ https-request https://www.betamark.com 
```

## Licence

```
    ____       __                             __  
   / __ )___  / /_____ _____ ___  ____ ______/ /__
  / __  / _ \/ __/ __ `/ __ `__ \/ __ `/ ___/ //_/
 / /_/ /  __/ /_/ /_/ / / / / / / /_/ / /  / ,<   
/_____/\___/\__/\__,_/_/ /_/ /_/\__,_/_/  /_/|_|  
                                                  
Copyright (c) 2023-present Shlomi Nissan
https://betamark.com

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
