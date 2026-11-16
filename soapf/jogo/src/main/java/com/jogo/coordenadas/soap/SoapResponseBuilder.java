package com.jogo.coordenadas.soap;

//import java.util.Locale; String.format(Locale.ROOT, "%.15g", valor);

import org.springframework.stereotype.Component;

import com.jogo.coordenadas.model.Movimento;
import com.jogo.coordenadas.model.Pulo;


@Component 
public class SoapResponseBuilder {
    private static final String SOAP_NAMESPACE = "http://schemas.xmlsoap.org/soap/envelope/";

    private static final String APP_NAMESPACE = "http://coordenadas.jogo2d.com/soap";

    public String construirResposta(Movimento movimento){
        String posicaoFinalX = formatarNumero(movimento.getPosicaoFinalX());
    
        return """
            <?xml version="1.0" encoding="UTF-8"?>
            <soap:Envelope
                xmlns:soap="%s"
                xmlns:tns="%s">
                <soap:Body>
                    <tns:CalcularMovimentoResponse>
                        <tns:posicaoFinalX>%s</tns:posicaoFinalX>
                    </tns:CalcularMovimentoResponse>
                </soap:Body>
            </soap:Envelope>
        """.formatted(SOAP_NAMESPACE, APP_NAMESPACE, posicaoFinalX);
    }

    public String construirResposta(Pulo pulo) {

        String posicaoFinalY = formatarNumero(pulo.getPosicaoFinalY());
        
        String velocidadeNova = formatarNumero(pulo.getVelocidadeNova());

        return """
            <?xml version="1.0" encoding="UTF-8"?>
            <soap:Envelope
                xmlns:soap="%s"
                xmlns:tns="%s">
                <soap:Body>
                    <tns:CalcularPuloResponse>
                        <tns:posicaoFinalY>%s</tns:posicaoFinalY>
                        <tns:velocidadeNova>%s</tns:velocidadeNova>
                    </tns:CalcularPuloResponse>
                </soap:Body>
            </soap:Envelope>
            """.formatted(SOAP_NAMESPACE, APP_NAMESPACE, posicaoFinalY, velocidadeNova);
    }

    private String formatarNumero(double valor) {
        return  Double.toString(valor);
    }

}
