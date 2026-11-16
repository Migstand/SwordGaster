package com.jogo.coordenadas.model;

public class PuloRequest {
    
    private final double posicaoAtualY;
    private final double gravidade;
    private final double velocidade;
    private final double deltaTempo;

    public PuloRequest( double posicaoAtualY, double gravidade, double velocidade, double deltaTempo){
        this.posicaoAtualY = posicaoAtualY;
        this.gravidade = gravidade;
        this.velocidade = velocidade;
        this.deltaTempo = deltaTempo;
    }

    public double getPosicaoAtualY(){
        return posicaoAtualY;
    }
    
    public double getGravidade(){
        return gravidade;
    }
    
    public double getVelocidade(){
        return velocidade;
    }
    
    public double getDeltaTempo(){
        return deltaTempo;
    }
}
