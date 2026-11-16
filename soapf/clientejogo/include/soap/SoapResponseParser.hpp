#ifndef SOAP_RESPONSE_PARSER_HPP
#define SOAP_RESPONSE_PARSER_HPP

#include <string>

struct SoapFault {
    std::string codigo;
    std::string mensagem;
};

class SoapResponseParser {
public:
    bool extrairPosicaoFinalX(
        const std::string& xml,
        double& posicaoFinalX
    );

    bool extrairResultadoPulo(
        const std::string& xml,
        double& posicaoFinalY,
        double& velocidadeNova
    );

    bool extrairSoapFault(
        const std::string& xml,
        SoapFault& fault
    );
};

#endif