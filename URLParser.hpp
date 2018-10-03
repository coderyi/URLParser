//
//  URLParser.hpp
//  URLParser
//
//  Created by coderyi on 2018/9/9.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#if __cplusplus > 199711L
#define register // Deprecated in C++11
#endif

namespace http {
    struct url {
        std::string protocol, user, password, host, path, search;
        int port;
    };
    
    /*
     Helper Functions
     */
    static inline std::string TailSlice(std::string &subject, std::string delimiter, bool keep_delim=false) {
        auto delimiter_location = subject.find(delimiter);
        auto delimiter_length = delimiter.length();
        std::string output = "";
        
        if (delimiter_location < std::string::npos) {
            auto start = keep_delim ? delimiter_location : delimiter_location + delimiter_length;
            auto end = subject.length() - start;
            output = subject.substr(start, end);
            subject = subject.substr(0, delimiter_location);
        }
        return output;
    }

    static inline std::string HeadSlice(std::string &subject, std::string delimiter) {
        auto delimiter_location = subject.find(delimiter);
        auto delimiter_length = delimiter.length();
        std::string output = "";
        if (delimiter_location < std::string::npos) {
            output = subject.substr(0, delimiter_location);
            subject = subject.substr(delimiter_location + delimiter_length, subject.length() - (delimiter_location + delimiter_length));
        }
        return output;
    }
    
    /*
     Extractors
     */
    static inline int ExtractPort(std::string &hostport) {
        int port;
        std::string portstring = TailSlice(hostport, ":");
        try { port = atoi(portstring.c_str()); }
        catch (std::exception e) { port = -1; }
        return port;
    }

    static inline std::string ExtractPath(std::string &in) { return TailSlice(in, "/", true); }
    static inline std::string ExtractProtocol(std::string &in) { return HeadSlice(in, "://"); }
    static inline std::string ExtractSearch(std::string &in) { return TailSlice(in, "?"); }
    static inline std::string ExtractPassword(std::string &userpass) { return TailSlice(userpass, ":"); }
    static inline std::string ExtractUserpass(std::string &in) { return HeadSlice(in, "@"); }
    
    /* Public Interface
     */
    static inline url ParseHTTPURL(std::string &in) {
        url ret;
        
        std::string tempIn = in;
        ret.port = -1;
        
        ret.protocol = ExtractProtocol(tempIn);
        ret.search = ExtractSearch(tempIn);
        ret.path = ExtractPath(tempIn);
        std::string userpass = ExtractUserpass(tempIn);
        ret.password = ExtractPassword(userpass);
        ret.user = userpass;
        ret.port = ExtractPort(tempIn);
        ret.host = tempIn;
        
        return ret;
    }
    
    /*
     URL Encode & Decode
     */
    std::string URLEncode(const std::string &str_source)
    {
        char const *in_str = str_source.c_str();
        int in_str_len = strlen(in_str);
        std::string out_str;
        register unsigned char c;
        unsigned char *to, *start;
        unsigned char const *from, *end;
        unsigned char hexchars[] = "0123456789ABCDEF";
        
        from = (unsigned char *)in_str;
        end = (unsigned char *)in_str + in_str_len;
        start = to = (unsigned char *)malloc(3 * in_str_len + 1);
        
        while (from < end) {
            c = *from++;
            
            if (c == ' ') {
                *to++ = '+';
            }
            else if ((c < '0' && c != '-' && c != '.') ||
                     (c < 'A' && c > '9') ||
                     (c > 'Z' && c < 'a' && c != '_') ||
                     (c > 'z')) {
                to[0] = '%';
                to[1] = hexchars[c >> 4]; // equal hexchars[c / 16];
                to[2] = hexchars[c & 15]; // equal hexchars[c % 16];
                to += 3;
            }
            else {
                *to++ = c;
            }
        }
        *to = 0;
        
        out_str = (char *)start;
        free(start);
        return out_str;
    }

    int _htoi(char *s)
    {
        int value;
        int c;
        
        c = ((unsigned char *)s)[0];
        if (isupper(c))
            c = tolower(c);
        value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;
        
        c = ((unsigned char *)s)[1];
        if (isupper(c))
            c = tolower(c);
        value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
        
        return (value);
    }
    
    std::string URLDecode(const std::string &str_source)
    {
        char const *in_str = str_source.c_str();
        int in_str_len = strlen(in_str);
        std::string out_str;
        char *str;
        
        str = strdup(in_str);
        
        char *dest = str;
        char *data = str;
        
        while (in_str_len--) {
            if (*data == '+') {
                *dest = ' ';
            }
            else if (*data == '%' && in_str_len >= 2 && isxdigit((int) *(data + 1))
                     && isxdigit((int) *(data + 2))) {
                *dest = (char)_htoi(data + 1);
                data += 2;
                in_str_len -= 2;
            }
            else {
                *dest = *data;
            }
            data++;
            dest++;
        }
        *dest = '\0';
        out_str = str;
        free(str);
        return out_str;
    }
    
}
