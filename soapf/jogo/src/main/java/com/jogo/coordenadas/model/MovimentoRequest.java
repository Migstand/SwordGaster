package com.jogo.coordenadas.model;

public class MovimentoRequest {
    
    private final double posicaoAtualX;
    private final String direcao;
    private final double velocidade;

    public MovimentoRequest(double posicaoAtualX, String direcao, double velocidade){

        this.posicaoAtualX = posicaoAtualX;
        this.direcao = direcao;
        this.velocidade = velocidade;

    }

    public double getPosicaoAtualX(){
        return posicaoAtualX;
    }

    public String getDirecao(){
        return direcao;
    }

    public double getVelocidade(){
        return velocidade;
    }
}
