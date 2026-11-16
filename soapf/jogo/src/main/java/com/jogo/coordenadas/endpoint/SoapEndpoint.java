
package com.jogo.coordenadas.endpoint;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;
import org.xml.sax.SAXException;

import com.jogo.coordenadas.soap.SoapFaultBuilder;
import com.jogo.coordenadas.soap.SoapRequestProcessor;

@Controller
public class SoapEndpoint {

    private static final Logger logger =
        LoggerFactory.getLogger(SoapEndpoint.class);

    private static final MediaType SOAP_MEDIA_TYPE =
        MediaType.parseMediaType("text/xml;charset=UTF-8");

    private final SoapRequestProcessor requestProcessor;
    private final SoapFaultBuilder faultBuilder;

    public SoapEndpoint(
            SoapRequestProcessor requestProcessor,
            SoapFaultBuilder faultBuilder) {

        this.requestProcessor = requestProcessor;
        this.faultBuilder = faultBuilder;
    }

    @PostMapping(
        value = "/ws",
        consumes = MediaType.TEXT_XML_VALUE,
        produces = MediaType.TEXT_XML_VALUE
    )
    @ResponseBody
    public ResponseEntity<String> receberMensagem(
            @RequestBody String xml) {

        try {

            String resposta = requestProcessor.processar(xml);

            return ResponseEntity.ok()
                .contentType(SOAP_MEDIA_TYPE)
                .body(resposta);

        } catch (IllegalArgumentException e) {

            String fault = faultBuilder.construirFault(
                "Client",
                e.getMessage()
            );

            return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(SOAP_MEDIA_TYPE)
                .body(fault);

        } catch (SAXException e) {

            String fault = faultBuilder.construirFault(
                "Client",
                "XML inválido ou malformado."
            );

            return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(SOAP_MEDIA_TYPE)
                .body(fault);

        } catch (ParserConfigurationException | IOException e) {

            logger.error("Erro na configuração ou leitura do XML.", e);

            String fault = faultBuilder.construirFault(
                "Server",
                "Não foi possível processar a mensagem XML."
            );

            return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(SOAP_MEDIA_TYPE)
                .body(fault);

        } catch (Exception e) {

            logger.error("Falha interna durante o processamento SOAP.", e);

            String fault = faultBuilder.construirFault(
                "Server",
                "Ocorreu uma falha interna durante o processamento."
            );

            return ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .contentType(SOAP_MEDIA_TYPE)
                .body(fault);
        }
    }
}


// V1:
// package com.jogo.coordenadas.endpoint;

// import java.io.IOException;

// import javax.xml.parsers.ParserConfigurationException;

// import org.springframework.http.HttpStatus;

// import org.springframework.http.MediaType;
// import org.springframework.http.ResponseEntity;
// import org.springframework.stereotype.Controller;
// import org.springframework.web.bind.annotation.PostMapping;
// import org.springframework.web.bind.annotation.RequestBody;
// import org.springframework.web.bind.annotation.ResponseBody;

// import org.xml.sax.SAXException;

// import com.jogo.coordenadas.soap.SoapFaultBuilder;
// import com.jogo.coordenadas.soap.SoapRequestProcessor;

// @Controller
// public class SoapEndpoint {

//     private final SoapRequestProcessor requestProcessor;
//     private final SoapFaultBuilder faultBuilder;

//     public SoapEndpoint(SoapRequestProcessor requestProcessor, SoapFaultBuilder faultBuilder){
//         this.requestProcessor = requestProcessor;
//         this.faultBuilder = faultBuilder;
//     }


//     @PostMapping(
//         value = "/ws",
//         consumes = MediaType.TEXT_XML_VALUE,
//         produces = MediaType.TEXT_XML_VALUE
//     )
//     @ResponseBody 
//     public ResponseEntity<String> receberMensagem(
//         @RequestBody String xml) {

//         try {
//             String resposta = requestProcessor.processar(xml);

//             return ResponseEntity.ok()
//                 .contentType(MediaType.TEXT_XML)
//                 .body(resposta);
//         } catch (IllegalArgumentException | SAXException e){

//             String fault = faultBuilder.construirFault("Client", e.getMessage());

//             return ResponseEntity
//                 .status(HttpStatus.BAD_REQUEST)
//                 .contentType(MediaType.TEXT_XML)
//                 .body(fault);
//         } catch (
//             ParserConfigurationException 
//             | IOException e
//         ) {
            
//             System.err.println("Erro durante o processamento XML:");
//             e.printStackTrace();

//             String fault = faultBuilder.construirFault("Server", "Não foi possível processar a mensagem XML.");

//             return ResponseEntity
//                 .status(HttpStatus.INTERNAL_SERVER_ERROR)
//                 .contentType(MediaType.TEXT_XML)
//                 .body(fault);
        
//         } catch (Exception e) {

//             e.printStackTrace();

//             String fault = faultBuilder.construirFault("Server", "Ocorreu uma falha interna durante o processamento."
//             );

//             return ResponseEntity
//                 .status(HttpStatus.INTERNAL_SERVER_ERROR)
//                 .contentType(MediaType.TEXT_XML)
//                 .body(fault);
//         }
//     }
    
// }