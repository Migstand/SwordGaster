package com.jogo.coordenadas.service;

import org.springframework.stereotype.Service;

import com.jogo.coordenadas.model.Movimento;
import com.jogo.coordenadas.model.Pulo;

@Service 
public class CoordenadasService {
    
    public Movimento calcularMovimento(double posicaoAtualX, String direcao, double velocidade) {

        //Validar os valores recebidos
        validarNumero(posicaoAtualX, "Posição atual X");
        validarNumero(velocidade, "Velocidade");
        
        if (velocidade < 0){
            throw new IllegalArgumentException(
                "A velocidade não pode ser negativa."
            );
        }

        double posicaoFinalX;

        if ("DIREITA".equals(direcao)){
            posicaoFinalX = posicaoAtualX + velocidade;
        } else if ("ESQUERDA".equals(direcao)){
            posicaoFinalX = posicaoAtualX - velocidade;
        } else {
            throw new IllegalArgumentException( "Direção inválida. Utilize DIREITA ou ESQUERDA");
        }

        validarNumero(posicaoFinalX, "Posição final X");

        return new Movimento(posicaoFinalX);
    }   

    public Pulo calcularPulo( double posicaoAtualY, double gravidade,
        double velocidade, double deltaTempo) {

        //Validar os valores recebidos
        validarNumero(posicaoAtualY, "Posição atual Y");
        validarNumero(gravidade, "Gravidade");
        validarNumero(velocidade, "Velocidade vertical");
        validarNumero(deltaTempo, "Delta tempo");

        if (gravidade < 0){
            throw new IllegalArgumentException("A gravidade não pode ser negativa.");
        }
        
        if (deltaTempo < 0){
            throw new IllegalArgumentException("O delta tempo não pode ser negativo.");
        }

        //Calcular a nova posição vertical
        double posicaoFinalY = posicaoAtualY + (velocidade * deltaTempo) 
        + (gravidade * Math.pow(deltaTempo, 2)) / 2;

        //Cacular a nova velocidade vertical
        double velocidadeNova = velocidade + (gravidade * deltaTempo);

        validarNumero(posicaoFinalY, "Posição final Y");
        validarNumero(velocidadeNova, "Nova velocidade");

        return new Pulo(posicaoFinalY, velocidadeNova);
    }

    public void validarNumero(double valor, String campo){

        if (!Double.isFinite(valor)){
            throw new IllegalArgumentException( campo + " deve ser um número finito.");
        }
    }

}
