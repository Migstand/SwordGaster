#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <SFML/Graphics.hpp>
#include <optional>

class Personagem {
private:
    sf::RectangleShape corpo;
    double posicaoX;
    double posicaoY;
    double velocidadeVertical;
    bool estaNoChao;

    sf::Texture textura;
    std::optional<sf::Sprite> sprite;

public:
    Personagem(double x, double y);

    void desenhar(sf::RenderWindow& janela);
    
    void atualizarPosicaoX(double x);
    void atualizarPosicaoY(double y);

    double obterPosicaoX() const;
    double obterPosicaoY() const;

    void atualizarVelocidadeVertical(double velocidade);
    double obterVelocidadeVertical() const;
    void atualizarEstadoChao(bool estado);
    bool estaApoiadoNoChao() const;

    sf::FloatRect obterLimites() const;
};

#endif