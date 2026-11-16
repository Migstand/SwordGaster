package com.jogo.coordenadas.soap;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;

import org.springframework.stereotype.Component;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import com.jogo.coordenadas.model.MovimentoRequest;
import com.jogo.coordenadas.model.PuloRequest;
import com.jogo.coordenadas.service.CoordenadasService;
import com.jogo.coordenadas.model.Movimento;
import com.jogo.coordenadas.model.Pulo;

@Component 
public class SoapRequestProcessor {
    
    private final SoapXmlParser xmlParser;
    private final SoapEnvelopeValidator envelopeValidator;
    private final SoapOperationParser operationParser;
    private final SoapParameterParser parameterParser;
    private final CoordenadasService coordenadasService;
    private final SoapResponseBuilder responseBuilder;

    public SoapRequestProcessor( SoapXmlParser xmlParser, SoapEnvelopeValidator envelopeValidator, SoapOperationParser operationParser, SoapParameterParser parameterParser, CoordenadasService coordenadasService, SoapResponseBuilder responseBuilder) {
        this.xmlParser = xmlParser;
        this.envelopeValidator = envelopeValidator;
        this.operationParser = operationParser;
        this.parameterParser = parameterParser;
        this.coordenadasService = coordenadasService;
        this.responseBuilder = responseBuilder;
    }

    public String processar(String xml) throws ParserConfigurationException, SAXException, IOException{
        // 1. Converter o XML em Document
        Document document = xmlParser.parse(xml);

        // 2. Validar o Envelope e localizar o Body
        Element body = envelopeValidator.localizarBody(document);

        // 3. Identificar a operação solicitada
        Element operacao = operationParser.identificarOperacao(body);

        String nomeOperacao = operacao.getLocalName();

         // 4. Extrair os parâmetros e executar o cálculo
        if ("CalcularMovimento".equals(nomeOperacao)){
            MovimentoRequest requisicao =  parameterParser.extrairMovimento(operacao);

            Movimento resultado = coordenadasService.calcularMovimento(
            requisicao.getPosicaoAtualX(),
            requisicao.getDirecao(),
            requisicao.getVelocidade());

            return responseBuilder.construirResposta(resultado);
        }

        if ("CalcularPulo".equals(nomeOperacao)){
            PuloRequest requisicao = parameterParser.extrairPulo(operacao);

            Pulo resultado = coordenadasService.calcularPulo(
            requisicao.getPosicaoAtualY(),
            requisicao.getGravidade(),
            requisicao.getVelocidade(),
            requisicao.getDeltaTempo());

            return responseBuilder.construirResposta(resultado);

        }

        throw new IllegalArgumentException( "Operação SOAP não reconhecida.");
    }

    
}
