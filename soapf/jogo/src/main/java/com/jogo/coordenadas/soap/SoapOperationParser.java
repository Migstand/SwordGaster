package com.jogo.coordenadas.soap;

import org.springframework.stereotype.Component;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;


@Component 
public class SoapOperationParser {
    
    private static final String APP_STRING =  "http://coordenadas.jogo2d.com/soap";

    public Element identificarOperacao(Element body){
        if (body == null) {
            throw new IllegalArgumentException("O body SOAP não pode ser nulo.");
        }

        Element operacao = null;

        NodeList filhos = body.getChildNodes();

        for (int i = 0; i < filhos.getLength(); i++) {
            Node filho = filhos.item(i);

            if (filho.getNodeType() == Node.ELEMENT_NODE){

                if (operacao != null) {
                    throw new IllegalArgumentException("O body deve possuir apenas uma operação");
                }

                Element elemento = (Element) filho;

                if (!APP_STRING.equals(elemento.getNamespaceURI())) {

                    throw new IllegalArgumentException("A operação pertence a um namespace inválido");
                }

                operacao = elemento;
            } else if (
                filho.getNodeType() == Node.TEXT_NODE || filho.getNodeType() == Node.CDATA_SECTION_NODE
            ) {       
                if (!filho.getTextContent().isBlank()) {
                    throw new IllegalArgumentException("Conteúdo textual inesperado no Body.");
                } 
            }
        }

        if (operacao == null) {
            throw new IllegalArgumentException("Nenhuma operação foi encontrada no Body");
        }

        String nome = operacao.getLocalName();

        if (!"CalcularMovimento".equals(nome) && !"CalcularPulo".equals(nome)) {
            throw new IllegalArgumentException("Operação SOAP desconhecida" + nome);
        }

        return operacao;
    }
}
