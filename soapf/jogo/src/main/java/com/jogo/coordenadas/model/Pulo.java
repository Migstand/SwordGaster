package com.jogo.coordenadas.model;

public class Pulo {
    
    private final double posicaoFinalY;
    private final double velocidadeNova;

    public Pulo (double posicaoFinalY, double velocidadeNova){
        this.posicaoFinalY = posicaoFinalY;
        this.velocidadeNova = velocidadeNova;
    }

    public double getPosicaoFinalY(){
        return posicaoFinalY;
    }

    public  double getVelocidadeNova(){
        return velocidadeNova;
    }
}
