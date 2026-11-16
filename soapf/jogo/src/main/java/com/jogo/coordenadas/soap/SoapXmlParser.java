package com.jogo.coordenadas.soap;

import java.io.IOException;
import java.io.StringReader;

import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;


import org.springframework.stereotype.Component;
import org.w3c.dom.Document;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

@Component 
public class SoapXmlParser {
    
    public Document parse(String xml) throws ParserConfigurationException, SAXException, IOException{
        if (xml == null || xml.isBlank()){
            throw new IllegalArgumentException("A mensagem XML está vazia.");
        }    

        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();

        //Habilitar reconhecimento de namespaces
        factory.setNamespaceAware(true);

        // Habilitar processamento XML seguro
        factory.setFeature(
            XMLConstants.FEATURE_SECURE_PROCESSING, true
        );

        // Impedir declarações DOCTYPE
        factory.setFeature("http://apache.org/xml/features/disallow-doctype-decl", true);

        // Desabilitar entidades externas
        factory.setFeature("http://xml.org/sax/features/external-general-entities", false);

        factory.setFeature("http://xml.org/sax/features/external-parameter-entities", false);

        // Desabilitar recursos adicionais
        factory.setXIncludeAware(false);
        factory.setExpandEntityReferences(false);

        //Bloquear acesso externo a DID e schemas
        factory.setAttribute(XMLConstants.ACCESS_EXTERNAL_DTD, "");
        factory.setAttribute(XMLConstants.ACCESS_EXTERNAL_SCHEMA, "");

        // Criar o parser
        DocumentBuilder builder = factory.newDocumentBuilder();

        // Interpretar o XML recebido
        return builder.parse(
            new InputSource(new StringReader(xml))
        );
    }
}
