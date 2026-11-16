#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>
#include "comunicacao/HttpResponse.hpp"

class HttpClient {
public:
    HttpClient();

    HttpResponse enviarRequisicao(
        const std::string& url,
        const std::string& mensagem,
        const std::string& soapAction
    );
};

#endif