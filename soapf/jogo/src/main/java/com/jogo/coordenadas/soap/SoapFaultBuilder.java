package com.jogo.coordenadas.soap;

import org.springframework.stereotype.Component;

@Component 
public class SoapFaultBuilder {
    
    private static final String SOAP_NAMESPACE = "http://schemas.xmlsoap.org/soap/envelope/";

    public String construirFault( String codigo, String mensagem){
        String codigoValido = validarCodigo(codigo);

        String mensagemEscapada = escaparXml(mensagem);

        return """
            <?xml version="1.0" encoding="UTF-8"?>
            <soap:Envelope
                xmlns:soap="%s">
                <soap:Body>
                    <soap:Fault>
                        <faultcode>soap:%s</faultcode>
                        <faultstring>%s</faultstring>
                    </soap:Fault>
                </soap:Body>
            </soap:Envelope>
            """.formatted( SOAP_NAMESPACE, codigoValido, mensagemEscapada);
    }

    private String validarCodigo(String codigo) {
        
        if (codigo == null) {
            throw new IllegalArgumentException("Código SOAP Fault não informado.");
        }

        return switch (codigo) {
            case "Client",
                    "Server",
                    "VersionMismatch",
                    "MustUnderstand" -> codigo;

            default -> throw new IllegalArgumentException(
                "Código SOAP Fault inválido."
            );
        };
    }

    private String escaparXml(String texto){
        if (texto == null) {
            return "Erro não especificado.";
        }

        return texto
        .replace("&","&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
        .replace("\"", "&quot;")
        .replace("'", "&apos;");
    }
}
