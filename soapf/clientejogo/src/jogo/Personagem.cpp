#include "jogo/Personagem.hpp"
#include <stdexcept>

Personagem::Personagem(double x, double y)
    : posicaoX(x), posicaoY(y),
      velocidadeVertical(0.0),
      estaNoChao(true) {

    corpo.setSize(sf::Vector2f(40.f, 60.f));

    corpo.setFillColor(sf::Color::Blue);

    corpo.setPosition(sf::Vector2f(
        static_cast<float>(posicaoX),
        static_cast<float>(posicaoY)
    ));
    
    if (!textura.loadFromFile("assets/mega8.png")) {
        throw std::runtime_error(
            "Nao foi possivel carregar o personagem!"
        );
    }

    sprite.emplace(textura);
}

void Personagem::desenhar(sf::RenderWindow& janela) {
    // janela.draw(corpo);
    if (sprite) {

        sprite->setScale(sf::Vector2f(0.0526f, 0.0526f));

        sprite->setPosition(
            sf::Vector2f(
                static_cast<float>(posicaoX - 12.0),
                static_cast<float>(posicaoY - 22.0)
            )
        );

        janela.draw(*sprite);
    }
}

void Personagem::atualizarPosicaoX(double x) {
    posicaoX = x;

    corpo.setPosition(sf::Vector2f(
        static_cast<float>(posicaoX),
        static_cast<float>(posicaoY)
    ));
}

void Personagem::atualizarPosicaoY(double y) {
    posicaoY = y;

    corpo.setPosition(sf::Vector2f(
        static_cast<float>(posicaoX),
        static_cast<float>(posicaoY)
    ));
}


double Personagem::obterPosicaoX() const {
    return posicaoX;
}

double Personagem::obterPosicaoY() const {
    return posicaoY;
}

void Personagem::atualizarVelocidadeVertical(double velocidade) {
    velocidadeVertical = velocidade;
}

double Personagem::obterVelocidadeVertical() const {
    return velocidadeVertical;
}
void Personagem::atualizarEstadoChao(bool estado) {
    estaNoChao = estado;
}

bool Personagem::estaApoiadoNoChao() const {
    return estaNoChao;
}

sf::FloatRect Personagem::obterLimites() const {
    return corpo.getGlobalBounds();
}