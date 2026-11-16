
#ifndef SERVICO_COORDENADAS_HPP
#define SERVICO_COORDENADAS_HPP

#include <string>
#include <future>

#include "comunicacao/HttpClient.hpp"
#include "soap/SoapResponseParser.hpp"

struct ResultadoMovimento {
    bool sucesso = false;
    double posicaoFinalX = 0.0;
};

struct ResultadoPulo {
    bool sucesso = false;
    double posicaoFinalY = 0.0;
    double velocidadeNova = 0.0;
};

class ServicoCoordenadas {
private:
    HttpClient cliente;
    SoapResponseParser parser;

    std::string urlServidor;

public:
    std::future<ResultadoMovimento> calcularMovimentoAsync(
        double posicaoAtualX,
        const std::string& direcao,
        double velocidade
    );

    std::future<ResultadoPulo> calcularPuloAsync(
        double posicaoAtualY,
        double gravidade,
        double velocidade,
        double deltaTempo
    );

    explicit ServicoCoordenadas(
        const std::string& url
    );

    bool calcularMovimento(
        double posicaoAtualX,
        const std::string& direcao,
        double velocidade,
        double& posicaoFinalX
    );

    bool calcularPulo(
        double posicaoAtualY,
        double gravidade,
        double velocidade,
        double deltaTempo,
        double& posicaoFinalY,
        double& velocidadeNova
    );
};

#endif