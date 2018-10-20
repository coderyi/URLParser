#include <iostream>
#include "URLParser.hpp"

int main(int argc, const char *argv[])
{
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
    
    return 0;
}
