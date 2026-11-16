#include "jogo/ServicoCoordenadas.hpp"
#include <iostream>

ServicoCoordenadas::ServicoCoordenadas(
    const std::string& url
) : urlServidor(url) {
}


bool ServicoCoordenadas::calcularMovimento(
    double posicaoAtualX,
    const std::string& direcao,
    double velocidade,
    double& posicaoFinalX
) {
    std::string mensagem =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" "
        "xmlns:tns=\"http://coordenadas.jogo2d.com/soap\">"
        "<soap:Body>"
        "<tns:CalcularMovimento>"
        "<tns:posicaoAtualX>" + std::to_string(posicaoAtualX) + "</tns:posicaoAtualX>"
        "<tns:direcao>" + direcao + "</tns:direcao>"
        "<tns:velocidade>" + std::to_string(velocidade) + "</tns:velocidade>"
        "</tns:CalcularMovimento>"
        "</soap:Body>"
        "</soap:Envelope>";

    std::cout << "\n========== SERVICO SOAP ==========\n";
    std::cout << "Operacao: CalcularMovimento\n";
    std::cout << "\n--- XML ENVIADO ---\n";
    std::cout << mensagem << "\n";
    HttpResponse resposta = cliente.enviarRequisicao(
        urlServidor,
        mensagem,
        "http://coordenadas.jogo2d.com/soap/CalcularMovimento"
    );
    std::cout << "\n--- XML RECEBIDO ---\n";
    std::cout << resposta.corpo << "\n";
    std::cout << "Status HTTP: " << resposta.codigoHttp << "\n";

    if (resposta.erroCurl != CURLE_OK) {
        return false;
    }

    SoapFault fault;

    if (parser.extrairSoapFault(resposta.corpo, fault)) {
        return false;
    }

    if (resposta.codigoHttp < 200 || resposta.codigoHttp >= 300) {
        return false;
    }

    return parser.extrairPosicaoFinalX(
        resposta.corpo,
        posicaoFinalX
    );
}


bool ServicoCoordenadas::calcularPulo(
    double posicaoAtualY,
    double gravidade,
    double velocidade,
    double deltaTempo,
    double& posicaoFinalY,
    double& velocidadeNova
) {
    std::string mensagem =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" "
        "xmlns:tns=\"http://coordenadas.jogo2d.com/soap\">"
        "<soap:Body>"
        "<tns:CalcularPulo>"
        "<tns:posicaoAtualY>" + std::to_string(posicaoAtualY) + "</tns:posicaoAtualY>"
        "<tns:gravidade>" + std::to_string(gravidade) + "</tns:gravidade>"
        "<tns:velocidade>" + std::to_string(velocidade) + "</tns:velocidade>"
        "<tns:deltatempo>" + std::to_string(deltaTempo) + "</tns:deltatempo>"
        "</tns:CalcularPulo>"
        "</soap:Body>"
        "</soap:Envelope>";

    std::cout << "\n========== SERVICO SOAP ==========\n";
    std::cout << "Operacao: CalcularPulo\n";
    std::cout << "\n--- XML ENVIADO ---\n";
    std::cout << mensagem<< "\n";
    HttpResponse resposta = cliente.enviarRequisicao(
        urlServidor,
        mensagem,
        "http://coordenadas.jogo2d.com/soap/CalcularPulo"
    );

    std::cout << "\n--- XML RECEBIDO ---\n";
    std::cout << resposta.corpo << "\n";

    std::cout << "Status HTTP: " << resposta.codigoHttp << "\n";

    if (resposta.erroCurl != CURLE_OK) {
        return false;
    }

    SoapFault fault;

    if (parser.extrairSoapFault(resposta.corpo, fault)) {
        return false;
    }

    if (resposta.codigoHttp < 200 || resposta.codigoHttp >= 300) {
        return false;
    }

    return parser.extrairResultadoPulo(
        resposta.corpo,
        posicaoFinalY,
        velocidadeNova
    );
}

std::future<ResultadoMovimento>
ServicoCoordenadas::calcularMovimentoAsync(
    double posicaoAtualX,
    const std::string& direcao,
    double velocidade
) {
    return std::async(
        std::launch::async,
        [this, posicaoAtualX, direcao, velocidade]() {

            ResultadoMovimento resultado;

            resultado.sucesso = calcularMovimento(
                posicaoAtualX,
                direcao,
                velocidade,
                resultado.posicaoFinalX
            );

            return resultado;
        }
    );
}


std::future<ResultadoPulo>
ServicoCoordenadas::calcularPuloAsync(
    double posicaoAtualY,
    double gravidade,
    double velocidade,
    double deltaTempo
) {
    return std::async(
        std::launch::async,
        [this, posicaoAtualY, gravidade, velocidade, deltaTempo]() {

            ResultadoPulo resultado;

            resultado.sucesso = calcularPulo(
                posicaoAtualY,
                gravidade,
                velocidade,
                deltaTempo,
                resultado.posicaoFinalY,
                resultado.velocidadeNova
            );

            return resultado;
        }
    );
}