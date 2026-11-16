#include "comunicacao/HttpClient.hpp"
#include <curl/curl.h>

#include <string>

static size_t WriteCallback(
    void* conteudo,
    size_t tamanho,
    size_t quantidade,
    std::string* resposta
) {
    size_t tamanhoTotal = tamanho * quantidade;

    resposta->append(
        static_cast<char*>(conteudo),
        tamanhoTotal
    );

    return tamanhoTotal;
}

HttpClient::HttpClient(){
}
HttpResponse HttpClient::enviarRequisicao(
    const std::string& url,
    const std::string& mensagem,
    const std::string& soapAction
) {
    HttpResponse resposta;

    CURL* requisicao = curl_easy_init();

    if (requisicao == nullptr) {
        return resposta;
    }

    struct curl_slist* cabecalhos = nullptr;

    cabecalhos = curl_slist_append(
        cabecalhos,
        "Content-Type: text/xml; charset=UTF-8"
    );

    std::string cabecalhoSoapAction =
        "SOAPAction: \"" + soapAction + "\"";

    cabecalhos = curl_slist_append(
        cabecalhos,
        cabecalhoSoapAction.c_str()
    );
    curl_easy_setopt( requisicao, CURLOPT_HTTPHEADER, cabecalhos);

    curl_easy_setopt(requisicao, CURLOPT_URL, url.c_str());

    curl_easy_setopt(requisicao, CURLOPT_POST, 1L);

    curl_easy_setopt(
        requisicao,
        CURLOPT_POSTFIELDS,
        mensagem.c_str()
    );

    curl_easy_setopt(
        requisicao,
        CURLOPT_POSTFIELDSIZE,
        static_cast<long>(mensagem.size())
    );

    curl_easy_setopt(
        requisicao,
        CURLOPT_WRITEFUNCTION,
        WriteCallback
    );

    curl_easy_setopt(
        requisicao,
        CURLOPT_WRITEDATA,
        &resposta.corpo
    );

    curl_easy_setopt(
        requisicao,
        CURLOPT_CONNECTTIMEOUT,
        5L
    );

    curl_easy_setopt(
        requisicao,
        CURLOPT_TIMEOUT,
        60L
    );
    
    resposta.erroCurl = curl_easy_perform(requisicao);

    CURLcode resultadoInfo = curl_easy_getinfo(
        requisicao,
        CURLINFO_RESPONSE_CODE,
        &resposta.codigoHttp
    );
    
    curl_slist_free_all(cabecalhos);

    curl_easy_cleanup(requisicao);

    return resposta;
}