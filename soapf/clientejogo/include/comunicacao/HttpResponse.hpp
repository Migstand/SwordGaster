#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <curl/curl.h>

struct HttpResponse {
    std::string corpo;
    long codigoHttp = 0;
    CURLcode erroCurl = CURLE_OK;
};

#endif