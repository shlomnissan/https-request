# https-request
This is a simple cmd tool written in modern C++. It makes HTTP/S requests to a given host and prints the output.

- The goal of this project is to experiment with HTTP clients and OpenSSL. It is not a full-featured HTTP client. For a complete production-grade HTTP client library in C++, check out [express-client](https://github.com/shlomnissan/express-client).
- If you find this project informative or useful, please ⭐️ this repository to show your support.

### Features
- A command-line application that can run independently
- Supports both HTTP and HTTPS protocols
- Written in modern C++
- Cross-platform compatible

### Usage

After building the application, a binary will be generated for you.
If you used CMake, the executable is likely located in the `build/src/` directory.
Once you locate the executable, you can run it directly from the command line. For example:
```
$ https-request https://www.betamark.com 
```

### Licence

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