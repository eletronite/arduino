/*
  ledRGB
  
  Este código exemplifica o uso de um LED RGB Catodo Comum.
  Hardware Necessário:
   - LED RGB Catodo Comum
   - 2x Resistores de 100 ohms
   - 1x Resistor de 180 ohms
   - Fios
  mais informações: https://www.eletronite.com.br/projetos/utilizando-leds-rgb
  
  criado 27 Dezembro 2016
  por Ricardo Alcântara
  Licenciado por Eletronite (http://www.eletronite.com.br)
  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

// Definição de pinos
#define LED_VERMELHO 9
#define LED_VERDE 10
#define LED_AZUL 11

// Parâmetros da animação
#define DELAY 10

int i; // Variável para percorrer as intensidades de cada cor

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
  
  // Define os pinos do LED RGB como saída
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  // Configura início da animação setando o LED Vermelho com intensidade máxima
  analogWrite(LED_VERMELHO, 255);
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {

  // Sequência de animação
  // Esta sequência percorre as cores do espectro RGB de forma contínua
  // mantendo a saturação e luminância fixas e variando somente a matiz
  
  for(i = 0; i <= 255; i++) {
    analogWrite(LED_VERDE, i);
    delay(DELAY);
  }
  for(i = 255; i >= 0; i--) {
    analogWrite(LED_VERMELHO, i);
    delay(DELAY);
  }
  for(i = 0; i <= 255; i++) {
    analogWrite(LED_AZUL, i);
    delay(DELAY);
  }
  for(i = 255; i >= 0; i--) {
    analogWrite(LED_VERDE, i);
    delay(DELAY);
  }
  for(i = 0; i <= 255; i++) {
    analogWrite(LED_VERMELHO, i);
    delay(DELAY);
  }
  for(i = 255; i >= 0; i--) {
    analogWrite(LED_AZUL, i);
    delay(DELAY);
  }
}
