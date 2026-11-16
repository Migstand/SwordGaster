#ifndef CONTROLE_JOGO_HPP
#define CONTROLE_JOGO_HPP

#include <SFML/Window/Keyboard.hpp>

enum class ComandoJogo {
    MoverDireita,
    MoverEsquerda,
    Pular,
    Nenhum
};

class ControleJogo {
public:
    ComandoJogo interpretarTecla(int tecla);
    bool estaPressionada(sf::Keyboard::Key tecla);
};

#endif