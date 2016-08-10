/*
  botaoInteligente
  
  Este código implementa um botão inteligente utilizando ESP8266 e IFTTT.
  
  O botão funciona enviando eventos para o IFTTT, através de uma conexão
  à internet WiFi, que executa a ação desejada.
  Hardware Necessário:
   - ESP8266 ESP-01
   - Resistor de 1K ohm
   - Diodo 1N4148
   - Chave táctil
   - Suporte para pilhas AAA
   - Fios
  mais informações: https://github.com/eletronite/arduino/tree/master/projetos/Botao-Inteligente
  
  criado 10 Agosto 2016
  por Ricardo Alcântara
  Licenciado por Eletronite (http://www.eletronite.com.br)
  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "nome-do-wifi";
const char* password = "sua-senha-do-wifi";

const char* host = "maker.ifttt.com";
const char* eventName   = "botao";
const char* privateKey = "sua-chave-do-ifttt";

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(2, OUTPUT);     // Define GPIO2 como saída
  digitalWrite(2, HIGH);  // Coloca a saída em nível alto para manter chip ligado

  /*Serial.print("Conectando em ");
    Serial.println(ssid);*/

  WiFi.begin(ssid, password);

  // Aguarda conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // Tempo para aguardar conexão, pode ser diminuido para melhorar tempo de resposta
    //Serial.print(".");
  }

  /*Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("Endereço de IP: ");
    Serial.println(WiFi.localIP());*/
}

void loop() {

  /*Serial.print("Conectando em ");
    Serial.println(host);*/

  HTTPClient http;

  // Serial.print("[HTTP] início...\n");

  // Configuração de servidor e url
  // http.begin(host, 443,  String("/trigger/") + eventName + "/with/key/" + privateKey, true, "‎a9 81 e1 35 b3 7f 81 b9 87 9d 11 dd 48 55 43 2c 8f c3 ec 87"); //HTTPS
  http.begin(host, 80, String("/trigger/") + eventName + "/with/key/" + privateKey); //HTTP

  // Serial.print("[HTTP] GET...\n");
  // inicia conexão e envia header HTTP
  int httpCode = http.GET();

  /*if (httpCode) {
      // Header HTTP foi enviado e resposta do servidor foi processada
      Serial.printf("[HTTP] GET... código: %d\n", httpCode);

      // Arquivo encontrado no servidor
      if (httpCode == 200) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.print("[HTTP] GET... falha, nenhuma conexão ou nenhum servidor http\n");
    }*/

  digitalWrite(2, LOW); // Coloca saída em nível baixo para deligar chip
  delay(100);
}
