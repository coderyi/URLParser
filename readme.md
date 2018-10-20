一个解析，Encode 和 Decode URL的小型C++库。


示例

```
    std::string tempURL = "http://user:password@www.google.com:80/path?search";
    urlhelper::url parsed = urlhelper::ParseHTTPURL(tempURL);
    std::cout << "1 " << parsed.protocol << "\n"
              << "2 " << parsed.user << "\n"
              << "3 " << parsed.password << "\n"
              << "4 " << parsed.host << "\n"
              << "5 " << parsed.port << "\n"
              << "6 " << parsed.path << "\n"
              << "7 " << parsed.search << std::endl;
    
    std::cout << urlhelper::URLEncode(tempURL) << "\n";
    std::cout << urlhelper::URLDecode(urlhelper::URLEncode(tempURL)) << "\n";

```
