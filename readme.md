一个解析，Encode 和 Decode URL的小型C++库。


示例

```
    std::string tempURL = "http://user:password@www.google.com:80/path?search";
    http::url parsed = http::ParseHTTPURL(tempURL);
    std::cout << "1 " << parsed.protocol << "\n"
              << "2 " << parsed.user << "\n"
              << "3 " << parsed.password << "\n"
              << "4 " << parsed.host << "\n"
              << "5 " << parsed.port << "\n"
              << "6 " << parsed.path << "\n"
              << "7 " << parsed.search << std::endl;
    
    std::cout << http::URLEncode(tempURL) << "\n";
    std::cout << http::URLDecode(http::URLEncode(tempURL)) << "\n";

```