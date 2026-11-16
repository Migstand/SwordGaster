#include "soap/SoapResponseParser.hpp"

#include <pugixml.hpp>

bool SoapResponseParser::extrairPosicaoFinalX(
    const std::string& xml,
    double& posicaoFinalX
) {
    pugi::xml_document documento;

    pugi::xml_parse_result resultado =
        documento.load_string(xml.c_str());

    if (!resultado) {
        return false;
    }

    pugi::xml_node envelope =
        documento.child("soap:Envelope");

    if (!envelope) {
        return false;
    }

    pugi::xml_node body =
        envelope.child("soap:Body");

    if (!body) {
        return false;
    }

    pugi::xml_node operacao =
        body.child("tns:CalcularMovimentoResponse");

    if (!operacao) {
        return false;
    }

    pugi::xml_node elemento =
        operacao.child("tns:posicaoFinalX");

    if (!elemento) {
        return false;
    }

    posicaoFinalX = elemento.text().as_double();

    return true;
}

bool SoapResponseParser::extrairSoapFault(
    const std::string& xml,
    SoapFault& fault
) {
    pugi::xml_document documento;

    pugi::xml_parse_result resultado =
        documento.load_string(xml.c_str());

    if (!resultado) {
        return false;
    }

    pugi::xml_node envelope =
        documento.child("soap:Envelope");

    if (!envelope) {
        return false;
    }

    pugi::xml_node body =
        envelope.child("soap:Body");

    if (!body) {
        return false;
    }

    pugi::xml_node elementoFault =
        body.child("soap:Fault");

    if (!elementoFault) {
        return false;
    }

    pugi::xml_node elementoCodigo =
        elementoFault.child("faultcode");

    pugi::xml_node elementoMensagem =
        elementoFault.child("faultstring");

    if (!elementoCodigo || !elementoMensagem) {
        return false;
    }

    fault.codigo = elementoCodigo.text().as_string();
    fault.mensagem = elementoMensagem.text().as_string();

    return true;
}

bool SoapResponseParser::extrairResultadoPulo(
    const std::string& xml,
    double& posicaoFinalY,
    double& velocidadeNova
) {
    pugi::xml_document documento;

    pugi::xml_parse_result resultado =
        documento.load_string(xml.c_str());

    if (!resultado) {
        return false;
    }

    pugi::xml_node envelope =
        documento.child("soap:Envelope");

    if (!envelope) {
        return false;
    }

    pugi::xml_node body =
        envelope.child("soap:Body");

    if (!body) {
        return false;
    }

    pugi::xml_node operacao =
        body.child("tns:CalcularPuloResponse");

    if (!operacao) {
        return false;
    }

    pugi::xml_node elementoPosicao =
        operacao.child("tns:posicaoFinalY");

    pugi::xml_node elementoVelocidade =
        operacao.child("tns:velocidadeNova");

    if (!elementoPosicao || !elementoVelocidade) {
        return false;
    }

    posicaoFinalY = elementoPosicao.text().as_double();
    velocidadeNova = elementoVelocidade.text().as_double();

    return true;
}