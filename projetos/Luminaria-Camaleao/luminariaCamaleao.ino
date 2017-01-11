/*
  luminariaCamaleao
  
  Este código implementa uma luminária que muda de cor de acordo com a cor
  da superficie que ela encosta.

  Hardware Necessário:
   - 2x LED RGB
   - 2x Resistores de 180 ohms
   - 4x Resistores de 100 ohms
   - Resistor de 10k ohms
   - LDR
   - Fios

  mais informações: http://www.eletronite.com.br/projetos/luminaria-camaleao
  
  criado 11 Janeiro 2017
  por Ricardo Alcântara

  Licenciado por Eletronite (http://www.eletronite.com.br)

  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

// Definição de pinos
#define ldr A0  
#define led_r 3
#define led_g 5
#define led_b 6
#define led_r_s 9  
#define led_g_s 10 
#define led_b_s 11 

// Parêmetros do sensor
#define toleraciaDeteccao 5
#define  mediasSensor 10

// Corretor Gamma
const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

int leitura_ldr[3];             // Variavel para armazenar a leitura atual do sensor
int color_cal[3], black_cal[3]; // Variáveis para armazenar o valor máximo e mínimo de leitura do sensor
int ambiente_cal, objeto_cal;   // Variáveis para guardar a intensidade luminosa do ambiente e do sensor tampado

// Variáveis para armazenar a ultima cor do sensor
unsigned char lastRed = 0, lastGreen = 0, lastBlue = 0;

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
  
  // Define os pinos dos LEDs RGB como saída
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_r_s, OUTPUT);
  pinMode(led_g_s, OUTPUT);
  pinMode(led_b_s, OUTPUT);
  
  // Certifica-se que os LEDs se iniciem apagados
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);
  digitalWrite(led_r_s, LOW);
  digitalWrite(led_g_s, LOW);
  digitalWrite(led_b_s, LOW);

  //aguarda 2 segundos para o início da calibração
  delay(2000);
  calibrar_sensor(); // Chama a rotina de calibração
  
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {

  while(analogRead(ldr) > objeto_cal); // Aguarda a aproximação de um objeto
  delay(500); // Delay para estabilização do objeto na área do sensor
  
  leSensor();   // Chama a rotina de leitura do sensor
  atualizaCores(); // Atualiza a cor do LED principal

  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

}

// Rotina de calibração do sensor
void calibrar_sensor() {
  
  // Analiza a luminosidade do ambiente
  ambiente_cal = mediaLeituras(mediasSensor);
  ambiente_cal -= ambiente_cal/toleraciaDeteccao; // Tolerância para facilitar detecção
  
  blinkLed(); // Pisca LED para indicar a sequência na calibração

  digitalWrite(led_r, HIGH);
  digitalWrite(led_g, HIGH);
  digitalWrite(led_b, HIGH);
  
  // Analiza a intesidade de luz com o objeto colocado em frente ao sensor
  objeto_cal = mediaLeituras(mediasSensor);
  objeto_cal += objeto_cal/toleraciaDeteccao; // Tolerância para facilitar detecção

  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);
  
  blinkLed();
  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

  // Início de calibração para valor máximo de leitura do sensor
  color_cal[0] = 0;
  color_cal[1] = 0;
  color_cal[2] = 0;

  blinkLed();
  
  while(analogRead(ldr) > objeto_cal); // Aguarda a aproximação de um objeto
  delay(500); // Delay para estabilização do objeto na área do sensor

  // São realizadas 10 medidas para encontrar o valor máximo registrado pelo sensor
  for(int i = 0; i < 10; i++)
  {
    
    digitalWrite(led_r_s, HIGH); // Acende o LED vermelho
    delay(100); // Aguarda 100ms para estabilizar o LDR

    // Realiza leitura do sensor e avalia se é o maior valor encontrado para o vermelho
    leitura_ldr[0] = mediaLeituras(mediasSensor);
    if (leitura_ldr[0] > color_cal[0]) {
      color_cal[0] = leitura_ldr[0];
    }
    
    digitalWrite(led_r_s, LOW); // Apaga o LED vermelho
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    digitalWrite(led_g_s, HIGH); // Acende o LED verde
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    // Realiza leitura do sensor e avalia se é o maior valor encontrado para o verde
    leitura_ldr[1] = mediaLeituras(mediasSensor);
    if (leitura_ldr[1] > color_cal[1]) {
      color_cal[1] = leitura_ldr[1];
    }
    
    digitalWrite(led_g_s, LOW); // Apaga o LED verde
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    digitalWrite(led_b_s, HIGH); // Acende o LED azul
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    // Realiza leitura do sensor e avalia se é o maior valor encontrado para o azul
    leitura_ldr[2] = mediaLeituras(mediasSensor);
    if (leitura_ldr[2] > color_cal[2]) {
      color_cal[2] = leitura_ldr[2];
    }
    
    digitalWrite(led_b_s, LOW); // Apaga o LED azul
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
  }
  
  blinkLed();
  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

  // Início de calibração para valor mínimo de leitura do sensor
  black_cal[0] = 1023;
  black_cal[1] = 1023;
  black_cal[2] = 1023;
  
  blinkLed();
  
  while(analogRead(A0) > objeto_cal); // Aguarda a aproximação de um objeto
  delay(500); // Delay para estabilização do objeto na área do sensor

  // São realizadas 10 medidas para encontrar o valor mínimo registrado pelo sensor
  for(int i = 0; i < 10; i++)
  {
    
    digitalWrite(led_r_s, HIGH);
    delay(100);
    
    leitura_ldr[0] = mediaLeituras(mediasSensor);
    if (leitura_ldr[0] < black_cal[0]) {
      black_cal[0] = leitura_ldr[0];
    }
    
    digitalWrite(led_r_s, LOW);
    delay(100);
    
    digitalWrite(led_g_s, HIGH);
    delay(100);
    
    leitura_ldr[1] = mediaLeituras(mediasSensor);
    if (leitura_ldr[1] < black_cal[1]) {
      black_cal[1] = leitura_ldr[1];
    }
    
    digitalWrite(led_g_s, LOW);
    delay(100);
    
    digitalWrite(led_b_s, HIGH);
    delay(100);
    
    leitura_ldr[2] = mediaLeituras(mediasSensor);
    if (leitura_ldr[2] < black_cal[2]) {
      black_cal[2] = leitura_ldr[2];
    }
    
    digitalWrite(led_b_s, LOW);
    delay(100);
    
  }
  
  blinkLed();
  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

  // Fim da calibração
  blinkLed();
}

// Rotina para piscar o LED durante 2 segundos
void blinkLed() {
  for(int i = 0; i < 10; i++) {
    digitalWrite(led_r, !digitalRead(led_r));
    digitalWrite(led_g, !digitalRead(led_g));
    digitalWrite(led_b, !digitalRead(led_b));
    delay(200);
  }
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);
  delay(100);
}

// Rotina para realizar média nas leituras do sensor
int mediaLeituras(int vezes) {
  
  int leitura;
  int acumulador = 0;
  
  // Soma a leitura do sensor à variável acumulador pelo número de vezes
  for(int i = 0; i < vezes; i++){
    leitura = analogRead(ldr);
    acumulador += leitura;
    delay(10);
  }
  
  // Calcula a média
  return((acumulador)/vezes);
  
}

// Rotina de leitura do sensor
void leSensor() {
  
  digitalWrite(led_r_s, HIGH); // Acende o LED vermelho
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  leitura_ldr[0] = mediaLeituras(mediasSensor); // Realiza a leitura do sensor
  
  digitalWrite(led_r_s, LOW); // Apaga o LED vermelho
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  digitalWrite(led_g_s, HIGH); // Acende o LED verde
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  leitura_ldr[1] = mediaLeituras(mediasSensor); // Realiza a leitura do sensor
  
  digitalWrite(led_g_s, LOW); // // Apaga o LED verde
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  digitalWrite(led_b_s, HIGH); // Acende o LED azul
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  leitura_ldr[2] = mediaLeituras(mediasSensor); // Realiza a leitura do sensor
  
  digitalWrite(led_b_s, LOW); // Apaga o LED azul
  
}

// Rotina para atualizar o valor da cor lida, convertida para a escala RGB
void atualizaCores() {

  // Converte o valor lido do sensor para a escala RGB (0 - 255)
  unsigned char red = constrain(map(leitura_ldr[0], black_cal[0], color_cal[0], 0, 255),0,255);
  unsigned char green = constrain(map(leitura_ldr[1], black_cal[1], color_cal[1], 0, 255),0,255);
  unsigned char blue = constrain(map(leitura_ldr[2], black_cal[2], color_cal[2], 0, 255),0,255);

  boolean atualizando = true;
  // Atualiza a cor do LED principal
  while(atualizando) {
    if(red > lastRed) {
      lastRed++;
      analogWrite(led_r, pgm_read_byte(&gamma8[lastRed]));
    } else if(red < lastRed) {
      lastRed--;
      analogWrite(led_r, pgm_read_byte(&gamma8[lastRed]));
    }
    if(green > lastGreen) {
      lastGreen++;
      analogWrite(led_g, pgm_read_byte(&gamma8[lastGreen]));
    } else if(green < lastGreen) {
      lastGreen--;
      analogWrite(led_g, pgm_read_byte(&gamma8[lastGreen]));
    }
    if(blue > lastBlue) {
      lastBlue++;
      analogWrite(led_b, pgm_read_byte(&gamma8[lastBlue]));
    } else if(blue < lastBlue) {
      lastBlue--;
      analogWrite(led_b, pgm_read_byte(&gamma8[lastBlue]));
    }
    delay(10);
    if(red == lastRed && green == lastGreen && blue == lastBlue)
      atualizando = false;
  }
  
}
