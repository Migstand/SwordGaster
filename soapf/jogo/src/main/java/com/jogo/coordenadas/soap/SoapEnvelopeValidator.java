package com.jogo.coordenadas.soap;

import org.springframework.stereotype.Component;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

@Component 
public class SoapEnvelopeValidator {
    public static final String SOAP_NAMESPACE = "http://schemas.xmlsoap.org/soap/envelope/";

    public Element localizarBody(Document document){
        if (document == null) {
            throw new IllegalArgumentException("O documento XML não pode ser nulo");
        }

        Element envelope = document.getDocumentElement();

        if (envelope == null
            || !"Envelope".equals(envelope.getLocalName())
            || !SOAP_NAMESPACE.equals(envelope.getNamespaceURI())){
        
            throw new IllegalArgumentException("Envelope SOAP 1.1 inválido.");
        }

        Element body = null;
        boolean headerEncontrado = false;
        boolean bodyEncontrado = false;

        NodeList filhos = envelope.getChildNodes();

        for (int i = 0; i < filhos.getLength(); i++){
            Node filho = filhos.item(i);

            if (filho.getNodeType() == Node.ELEMENT_NODE) {
                Element elemento = (Element) filho;

                if (!SOAP_NAMESPACE.equals(elemento.getNamespaceURI())) {

                    throw new IllegalArgumentException( "Elemento fora do namespace SOAP.");
                }

                String nome = elemento.getLocalName();

                if ("Header".equals(nome)){
                    if (headerEncontrado || bodyEncontrado){
                        throw new IllegalArgumentException("Header duplicado ou em posição inválida");
                    }

                    headerEncontrado = true;

                } else if ("Body".equals(nome)){

                    if (bodyEncontrado){
                        throw new IllegalArgumentException("A mensagem SOAP possui mais de um Body");

                    }

                    body = elemento;
                    bodyEncontrado = true;

                } else {
                    throw new IllegalArgumentException("Elemento inválido dentro do Envelope SOAP.");
                }

            } else if (
                filho.getNodeType() == Node.TEXT_NODE || filho.getNodeType() == Node.CDATA_SECTION_NODE) {
                if (!filho.getTextContent().isBlank()) {
                    throw new IllegalArgumentException("Conteúdo textual inválido dentro do Envelope");
                }       
            }    
        }

        if (body == null) {
            throw new IllegalArgumentException("A mensagem SOAP não possui um Body");
        }

        return body;
    }
}
