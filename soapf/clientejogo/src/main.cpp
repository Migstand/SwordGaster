#include <SFML/Graphics.hpp>
#include <curl/curl.h>
#include <pugixml.hpp>
#include <iostream>
#include "comunicacao/HttpClient.hpp"
#include "soap/SoapResponseParser.hpp"
#include "jogo/Personagem.hpp"
#include "jogo/ControleJogo.hpp"
#include "jogo/ServicoCoordenadas.hpp"
#include <mutex>
#include <thread>
#include <chrono>

const double VELOCIDADE_HORIZONTAL = 3.0;
const double GRAVIDADE = 980.0;
const double DELTA_TEMPO = 0.016;
const double VELOCIDADE_INICIAL_PULO = -450.0;
const double ALTURA_PERSONAGEM = 60.0;
const double POSICAO_CHAO = 460.0;
const double ALTURA_CHAO = POSICAO_CHAO - ALTURA_PERSONAGEM;

const double LARGURA_PERSONAGEM = 40.0;
const double PLATAFORMA_X = 400.0;
const double PLATAFORMA_Y = 380.0;
const double LARGURA_PLATAFORMA = 180.0;
const double ALTURA_PLATAFORMA = 20.0;

const double PLATAFORMA2_X = 150.0;
const double PLATAFORMA2_Y = 300.0;
const double LARGURA_PLATAFORMA2 = 160.0;
const double ALTURA_PLATAFORMA2 = 20.0;


bool sobreposicaoHorizontal(
    const sf::FloatRect& personagem,
    const sf::RectangleShape& plataforma
) {
    sf::FloatRect limitesPlataforma =
        plataforma.getGlobalBounds();

    return (
        personagem.position.x + personagem.size.x >
            limitesPlataforma.position.x
        &&
        personagem.position.x <
            limitesPlataforma.position.x + limitesPlataforma.size.x
    );
}

bool colidiuComPlataforma(
    const sf::FloatRect& personagem,
    const sf::RectangleShape& plataforma,
    double posicaoYAnterior,
    double velocidadeVerticalAnterior
) {
    sf::FloatRect limitesPlataforma =
        plataforma.getGlobalBounds();

    double baseAnterior =
        posicaoYAnterior + personagem.size.y;

    double baseAtual =
        personagem.position.y + personagem.size.y;

    return (
        velocidadeVerticalAnterior > 0.0 &&
        sobreposicaoHorizontal(personagem, plataforma) &&
        baseAnterior <= limitesPlataforma.position.y &&
        baseAtual >= limitesPlataforma.position.y
    );
}


int main() {
    CURLcode resultado = curl_global_init(CURL_GLOBAL_DEFAULT);

    ServicoCoordenadas servico(
        "http://172.17.0.1:8080/ws"
    );

    std::future<ResultadoMovimento> futuroMovimento;
    std::future<ResultadoPulo> futuroPulo;
    futuroMovimento = servico.calcularMovimentoAsync(
        60.0,
        "DIREITA",
        VELOCIDADE_HORIZONTAL
    );

    futuroPulo = servico.calcularPuloAsync(
        400.0,
        GRAVIDADE,
        -10.0,
        DELTA_TEMPO
    );

    ResultadoMovimento resultadoMovimento = futuroMovimento.get();
    ResultadoPulo resultadoPulo = futuroPulo.get();

    double posicaoFinalX = 60.0;
    double posicaoFinalY = 400.0;
    double velocidadeNova = 0.0;

    bool movimentoCalculado = resultadoMovimento.sucesso;
    bool puloCalculado = resultadoPulo.sucesso;

    if (movimentoCalculado) {
        posicaoFinalX = resultadoMovimento.posicaoFinalX;

        std::cout << "Posicao final X: "
                << posicaoFinalX << "\n";
    }

    if (puloCalculado) {
        posicaoFinalY = resultadoPulo.posicaoFinalY;
        velocidadeNova = resultadoPulo.velocidadeNova;

        std::cout << "Posicao final Y: "
                << posicaoFinalY << "\n";

        std::cout << "Nova velocidade vertical: "
                << velocidadeNova << "\n";
    }

    

    sf::RenderWindow janela(
        sf::VideoMode({800u, 600u}),
        "Cliente SOAP - Coordenadas 2D"
    );

    Personagem personagem(60.0, ALTURA_CHAO);

    if (movimentoCalculado) {
        personagem.atualizarPosicaoX(posicaoFinalX);
    }

    if (puloCalculado) {
        personagem.atualizarPosicaoY(posicaoFinalY);
    }
    // personagem.atualizarPosicaoX(300.0);
    // personagem.atualizarPosicaoY(250.0);

    ControleJogo controle;

    while (janela.isOpen()) {
        // CENARIO
        sf::RectangleShape chao(
            sf::Vector2f(800.0f, 140.0f)
        );

        chao.setPosition(
            sf::Vector2f(0.0f, 460.0f)
        );

        chao.setFillColor(
            sf::Color(90, 160, 75)
        );

        // PLATAFOMAS
        sf::RectangleShape plataforma(
            sf::Vector2f(
                static_cast<float>(LARGURA_PLATAFORMA),
                static_cast<float>(ALTURA_PLATAFORMA)
            )
        );

        plataforma.setPosition(
            sf::Vector2f(
                static_cast<float>(PLATAFORMA_X),
                static_cast<float>(PLATAFORMA_Y)
            )
        );

        plataforma.setFillColor(
            sf::Color(130, 85, 45)
        );

        sf::RectangleShape plataforma2(
            sf::Vector2f(
                static_cast<float>(LARGURA_PLATAFORMA2),
                static_cast<float>(ALTURA_PLATAFORMA2)
            )
        );

        plataforma2.setPosition(
            sf::Vector2f(
                static_cast<float>(PLATAFORMA2_X),
                static_cast<float>(PLATAFORMA2_Y)
            )
        );

        plataforma2.setFillColor(
            sf::Color(130, 85, 45)
        );

        // BACKGROUND
        sf::CircleShape nuvem1(25.0f);
        nuvem1.setPosition(sf::Vector2f(100.0f, 80.0f));
        nuvem1.setFillColor(sf::Color::White);

        sf::CircleShape nuvem2(35.0f);
        nuvem2.setPosition(sf::Vector2f(125.0f, 65.0f));
        nuvem2.setFillColor(sf::Color::White);

        sf::CircleShape nuvem3(25.0f);
        nuvem3.setPosition(sf::Vector2f(165.0f, 80.0f));
        nuvem3.setFillColor(sf::Color::White);

        sf::CircleShape nuvem4(25.0f);
        nuvem4.setPosition(sf::Vector2f(600.0f, 80.0f));
        nuvem4.setFillColor(sf::Color::White);

        sf::CircleShape nuvem5(35.0f);
        nuvem5.setPosition(sf::Vector2f(625.0f, 65.0f));
        nuvem5.setFillColor(sf::Color::White);

        sf::CircleShape nuvem6(25.0f);
        nuvem6.setPosition(sf::Vector2f(665.0f, 80.0f));
        nuvem6.setFillColor(sf::Color::White);

        if (
            futuroMovimento.valid() &&
            futuroMovimento.wait_for(std::chrono::milliseconds(0))
                == std::future_status::ready
        ) {
            ResultadoMovimento resultado = futuroMovimento.get();

            if (resultado.sucesso) {
                personagem.atualizarPosicaoX(resultado.posicaoFinalX);

                std::cout << "Nova posicao X: "
                        << resultado.posicaoFinalX << "\n";
            } else {
                std::cout << "Falha ao calcular movimento.\n";
            }
        }

        if (
            futuroPulo.valid() &&
            futuroPulo.wait_for(std::chrono::milliseconds(0))
                == std::future_status::ready
        ) {
            ResultadoPulo resultado = futuroPulo.get();
            double posicaoYAnterior = personagem.obterPosicaoY();
            double velocidadeVerticalAnterior = personagem.obterVelocidadeVertical();

            if (resultado.sucesso) {

                personagem.atualizarPosicaoY(
                    resultado.posicaoFinalY
                );

                personagem.atualizarVelocidadeVertical(
                    resultado.velocidadeNova
                );

                bool colidiuPrimeira = colidiuComPlataforma(
                    personagem.obterLimites(),
                    plataforma,
                    posicaoYAnterior,
                    velocidadeVerticalAnterior
                );

                bool colidiuSegunda = colidiuComPlataforma(
                    personagem.obterLimites(),
                    plataforma2,
                    posicaoYAnterior,
                    velocidadeVerticalAnterior
                );

                if (colidiuPrimeira || colidiuSegunda) {

                    if (colidiuPrimeira) {
                        personagem.atualizarPosicaoY(
                            PLATAFORMA_Y - ALTURA_PERSONAGEM
                        );
                    } else {
                        personagem.atualizarPosicaoY(
                            PLATAFORMA2_Y - ALTURA_PERSONAGEM
                        );
                    }

                    personagem.atualizarVelocidadeVertical(0.0);
                    personagem.atualizarEstadoChao(true);

                    std::cout << "Colisao com plataforma!\n";

                } else if (resultado.posicaoFinalY >= ALTURA_CHAO) {

                    personagem.atualizarPosicaoY(ALTURA_CHAO);
                    personagem.atualizarVelocidadeVertical(0.0);
                    personagem.atualizarEstadoChao(true);

                    std::cout << "Pulo finalizado.\n";

                } else {

                    futuroPulo = servico.calcularPuloAsync(
                        personagem.obterPosicaoY(),
                        GRAVIDADE,
                        personagem.obterVelocidadeVertical(),
                        DELTA_TEMPO
                    );
                }

            } else {
                std::cout << "Falha ao calcular pulo.\n";
            }
        }
        if (
            personagem.estaApoiadoNoChao() &&
            !futuroPulo.valid() &&
            personagem.obterPosicaoY() < ALTURA_CHAO &&
            !(
                sobreposicaoHorizontal(personagem.obterLimites(), plataforma)
                ||
                sobreposicaoHorizontal(personagem.obterLimites(), plataforma2)
            )
        ) {
            personagem.atualizarEstadoChao(false);

            personagem.atualizarVelocidadeVertical(0.0);

            futuroPulo = servico.calcularPuloAsync(
                personagem.obterPosicaoY(),
                GRAVIDADE,
                personagem.obterVelocidadeVertical(),
                DELTA_TEMPO
            );
        }

        if (controle.estaPressionada(sf::Keyboard::Key::Right)) {
            if (!futuroMovimento.valid()) {
                futuroMovimento = servico.calcularMovimentoAsync(
                    personagem.obterPosicaoX(),
                    "DIREITA",
                    VELOCIDADE_HORIZONTAL
                );
            }
        }

        if (controle.estaPressionada(sf::Keyboard::Key::Left)) {
            if (!futuroMovimento.valid()) {
                futuroMovimento = servico.calcularMovimentoAsync(
                    personagem.obterPosicaoX(),
                    "ESQUERDA",
                    VELOCIDADE_HORIZONTAL
                );
            }
        }
        while (const std::optional evento = janela.pollEvent()) {

            if (evento->is<sf::Event::Closed>()) {
                janela.close();
            }

            if (const auto* tecla = evento->getIf<sf::Event::KeyPressed>()) {
            
                ComandoJogo comando = controle.interpretarTecla(
                    static_cast<int>(tecla->code)
                );

                switch (comando) {

                    case ComandoJogo::MoverDireita:
                        // if (!futuroMovimento.valid()) {
                        //     futuroMovimento = servico.calcularMovimentoAsync(
                        //         personagem.obterPosicaoX(),
                        //         "DIREITA",
                        //         VELOCIDADE_HORIZONTAL
                        //     );

                        //     std::cout << "Solicitando movimento para direita...\n";
                        // }
                        // break;

                    case ComandoJogo::MoverEsquerda:
                        // if (!futuroMovimento.valid()) {
                        //     futuroMovimento = servico.calcularMovimentoAsync(
                        //         personagem.obterPosicaoX(),
                        //         "ESQUERDA",
                        //         VELOCIDADE_HORIZONTAL
                        //     );

                        //     std::cout << "Solicitando movimento para esquerda...\n";
                        // }
                        break;

                    case ComandoJogo::Pular:
                        if (!futuroPulo.valid() && 
                            personagem.estaApoiadoNoChao()
                        ) {
                            personagem.atualizarEstadoChao(false);

                            personagem.atualizarVelocidadeVertical(
                                VELOCIDADE_INICIAL_PULO
                            );
                            futuroPulo = servico.calcularPuloAsync(
                                personagem.obterPosicaoY(),
                                GRAVIDADE,
                                personagem.obterVelocidadeVertical(),
                                DELTA_TEMPO
                            );

                            std::cout << "Solicitando pulo...\n";
                        }
                        break;

                    case ComandoJogo::Nenhum:
                        break;
                }
            }

        }

        janela.clear(sf::Color(135, 206, 235));

        janela.draw(chao);
        janela.draw(plataforma);
        janela.draw(plataforma2);
        janela.draw(nuvem1);
        janela.draw(nuvem2);
        janela.draw(nuvem3);
        janela.draw(nuvem4);
        janela.draw(nuvem5);
        janela.draw(nuvem6);
        
        personagem.desenhar(janela);

        janela.display();
    }

    if (futuroMovimento.valid()) {
        futuroMovimento.wait();
    }

    if (futuroPulo.valid()) {
        futuroPulo.wait();
    }
    curl_global_cleanup();

    return 0;
}