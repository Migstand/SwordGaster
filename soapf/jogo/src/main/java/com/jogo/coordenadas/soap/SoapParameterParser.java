package com.jogo.coordenadas.soap;

import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Component;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.jogo.coordenadas.model.MovimentoRequest;
import com.jogo.coordenadas.model.PuloRequest;

@Component 
public class SoapParameterParser {
    
    private static final String APP_NAME_STRING = "http://coordenadas.jogo2d.com/soap";

    public MovimentoRequest extrairMovimento(Element operacao){

        List<String> valores = lerParametros(operacao, "CalcularMovimento", "posicaoAtualX", "direcao", "velocidade");
        
        double posicaoAtualX = converterDouble(valores.get(0), "posicaoAtualX");

        String direcao = valores.get(1);

        if (!"DIREITA".equals(direcao) && !"ESQUERDA".equals(direcao)){
            throw new IllegalArgumentException("Direção invalida. Utilize DIREITA ou ESQUERDA");
        }

        double velocidade = converterDouble(valores.get(2), "velocidade");

        return new MovimentoRequest(posicaoAtualX, direcao, velocidade);
    }

    public PuloRequest extrairPulo(Element operacao) {

        List<String> valores = lerParametros(operacao, "CalcularPulo", "posicaoAtualY", "gravidade", "velocidade", "deltatempo");

        double posicaoAtualY = converterDouble(valores.get(0), "posicaoAtualY");
        double gravidade = converterDouble(valores.get(1), "gravidade");
        double velocidade = converterDouble(valores.get(2), "velocidade");
        double deltaTempo = converterDouble(valores.get(3), "deltatempo");

        return new PuloRequest(posicaoAtualY, gravidade, velocidade, deltaTempo);
    }

    private List<String> lerParametros(Element operacao, String nomeOperacao, String... nomesEsperados){
        if (operacao == null || !APP_NAME_STRING.equals(operacao.getNamespaceURI()) || !nomeOperacao.equals(operacao.getLocalName())){
            throw new IllegalArgumentException("Elemento de operação inválido.");
        }

        List<Element> elementos = new ArrayList<>();
        NodeList filhos = operacao.getChildNodes();

        for (int i = 0; i < filhos.getLength(); i++){
            Node filho = filhos.item(i);

            if (filho.getNodeType() == Node.ELEMENT_NODE){
                elementos.add((Element) filho);
            } else if (filho.getNodeType() == Node.TEXT_NODE || filho.getNodeType() == Node.CDATA_SECTION_NODE){

                if (!filho.getTextContent().isBlank()){
                    throw new IllegalArgumentException("Texto inesperado entre parâmetros");
                }
            } else if (filho.getNodeType() != Node.COMMENT_NODE){
                throw new IllegalArgumentException("Conteúdo inesperado na operação.");
            }
        }

        if (elementos.size() != nomesEsperados.length){
            throw new IllegalArgumentException("Quantidade incorreta de parâmetros em "+ nomeOperacao + ".");
        }

        List<String> valores = new ArrayList<>();

        for (int i = 0; i < nomesEsperados.length; i++){
            Element elemento = elementos.get(i);

            if (!APP_NAME_STRING.equals(elemento.getNamespaceURI()) || !nomesEsperados[i].equals(elemento.getLocalName())) {
                throw new IllegalArgumentException( "Parâmetro inválido ou fora de ordem: " + nomesEsperados[i] + ".");
            }
            
            NodeList conteudo = elemento.getChildNodes();

            for (int j = 0; j < conteudo.getLength(); j++){
                if (conteudo.item(j).getNodeType() == Node.ELEMENT_NODE){
                    throw new IllegalArgumentException( "O parâmetro " + nomesEsperados[i] + " não pode possuir elementos internos.");
                }
            }

            String valor = elemento.getTextContent().trim();

            if (valor.isEmpty()){
                throw new IllegalArgumentException( "O parâmetro " + nomesEsperados[i] + " está vazio.");
            }

            valores.add(valor);

        }
        return valores;

    }

    private double converterDouble(String valor, String campo){
        try {
            double numero = Double.parseDouble(valor);

            if (!Double.isFinite(numero)){
                throw new IllegalArgumentException(campo + " deve ser um número finito.");
            }

            return numero;
        } catch (NumberFormatException e){throw new IllegalArgumentException( "O parâmetro " + campo + " não contém um número válido.");}
    }
}
