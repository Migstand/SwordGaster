
#include "jogo/ControleJogo.hpp"
#include <SFML/Window/Keyboard.hpp>

ComandoJogo ControleJogo::interpretarTecla(int tecla) {

    switch (static_cast<sf::Keyboard::Key>(tecla)) {

        case sf::Keyboard::Key::Right:
            return ComandoJogo::MoverDireita;

        case sf::Keyboard::Key::Left:
            return ComandoJogo::MoverEsquerda;

        case sf::Keyboard::Key::Space:
            return ComandoJogo::Pular;

        default:
            return ComandoJogo::Nenhum;
    }
}
bool ControleJogo::estaPressionada(sf::Keyboard::Key tecla) {
    return sf::Keyboard::isKeyPressed(tecla);
}