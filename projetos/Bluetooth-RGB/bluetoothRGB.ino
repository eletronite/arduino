/*
  bluetoothRGB
  
  Este código implementa o controle de um LED RGB através
  de um módulo bluetooth comunicando com um celular.
  Hardware Necessário:
   - Módulo Bluetooth HC-05
   - LED RGB Catodo Comum
   - 2x Resistores de 100 ohms
   - 1x Resistor de 180 ohms
   - Fios
  mais informações: https://www.eletronite.com.br/projetos/controlando-led-rgb-com-celular
  
  criado 03 Janeiro 2017
  por Ricardo Alcântara
  Licenciado por Eletronite (http://www.eletronite.com.br)
  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

#include <SoftwareSerial.h>

// Definição de pinos
#define LED_VERMELHO 5
#define LED_VERDE 6
#define LED_AZUL 9

//Define os pinos para o módulo bluetooth  
SoftwareSerial bluetooth(10, 11); // RX, TX  

byte coresRGB[3] = {255, 0, 0}; // Variável de controle das cores do LED

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {

  // Define os pinos do LED RGB como saída
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  // Configura o LED Vermelho com intensidade máxima
  analogWrite(LED_VERMELHO, 255);

  // Inicializa a comunicação com o módulo bluetooth
  bluetooth.begin(9600);
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {

  // Verifica se recebeu dados do módulo bluetooth
  if(bluetooth.available()) {
    bluetooth.readBytes(coresRGB, 3); // Armazena os valores RGB recebidos na variável
  }
  
  // Altera as cores do LED
  analogWrite(LED_VERMELHO, coresRGB[0]);
  analogWrite(LED_VERDE, coresRGB[1]);
  analogWrite(LED_AZUL, coresRGB[2]);
}
