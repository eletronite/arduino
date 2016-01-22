/*
  sensorCores
  
  Este código implementa um sensor de cores simples utilizando um LED RGB
  conectado aos pinos 9, 10, 11, e um LDR conectado ao pino A0.
  LEDs comuns podem ser utilizados no lugar do LED RGB, respeitando as cores
  vermelho, verde e azul.

  O sensor funciona medindo a intensidade de cada cor refletida no LDR quando 
  um objeto é aproximado, retornando valores de cor na escala RGB.

  Este código foi desenvolvido para ser utilizado juntamente com o programa 
  Processing, porém pode ser utilizado com o monitor serial.

  Hardware Necessário:
   - LED RGB
   - 3x Resistores de 220 ohms
   - Resistor de 10k ohms
   - LDR
   - Fios

  mais informações: https://github.com/eletronite/arduino/tree/master/projetos/Sensor-de-Cores
  
  criado 22 Janeiro 2016
  por Ricardo Alcântara

  Licenciado por Eletronite (http://www.eletronite.com.br)

  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

// Definição de pinos
#define ldr A0  
#define led_r 9  
#define led_g 10 
#define led_b 11 

// Parêmetros do sensor
#define toleraciaDeteccao 10
#define  mediasSensor 10

int leitura_ldr[3];             // Variavel para armazenar a leitura atual do sensor
int color_cal[3], black_cal[3]; // Variáveis para armazenar o valor máximo e mínimo de leitura do sensor
int ambiente_cal, objeto_cal;   // Variáveis para guardar a intensidade luminosa do ambiente e do sensor tampado

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
  
  // Define os pinos do LED RGB como saída
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);
  
  // Certifica-se que o LED se inicie apagado
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);
  
  // inicializa a comunicação serial em 9600 bits por segundo:
  Serial.begin(9600);

  // Aguarda um caractere qualquer para confirmar conexão com o Processing
  Serial.flush();
  while(!Serial.available());

  //aguarda 2 segundos para o início da calibração
  delay(2000);
  calibrar_sensor(); // Chama a rotina de calibração
  
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {

  while(analogRead(ldr) > objeto_cal); // Aguarda a aproximação de um objeto
  delay(500); // Delay para estabilização do objeto na área do sensor
  
  leSensor();   // Chama a rotina de leitura do sensor
  enviaCores(); // Envia as cores lidas para a porta serial

  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

}

// Rotina de calibração do sensor
void calibrar_sensor() {
  
  // Analiza a luminosidade do ambiente
  ambiente_cal = mediaLeituras(10);
  ambiente_cal -= ambiente_cal/10; // 10% de tolerância para facilitar detecção
  
  Serial.println("Aproxime um objeto qualquer ao sensor");
  delay(5000); // Aguarda 5 segundos para aproximação do objeto
  
  Serial.println("Calibrando...");

  // Analiza a intesidade de luz com o objeto colocado em frente ao sensor
  objeto_cal = mediaLeituras(10);
  objeto_cal += objeto_cal/10; // 10% de tolerância para facilitar detecção
  
  Serial.println("Remova o objeto");
  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

  // Início de calibração para valor máximo de leitura do sensor
  color_cal[0] = 0;
  color_cal[1] = 0;
  color_cal[2] = 0;

  Serial.println("Aproxime um objeto branco");
  
  while(analogRead(ldr) > objeto_cal); // Aguarda a aproximação de um objeto
  delay(500); // Delay para estabilização do objeto na área do sensor

  Serial.println("Calibrando...");

  // São realizadas 10 medidas para encontrar o valor máximo registrado pelo sensor
  for(int i = 0; i < 10; i++)
  {
    
    digitalWrite(led_r, HIGH); // Acende o LED vermelho
    delay(100); // Aguarda 100ms para estabilizar o LDR

    // Realiza leitura do sensor e avalia se é o maior valor encontrado para o vermelho
    leitura_ldr[0] = mediaLeituras(10);
    if (leitura_ldr[0] > color_cal[0]) {
      color_cal[0] = leitura_ldr[0];
    }
    
    digitalWrite(led_r, LOW); // Apaga o LED vermelho
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    digitalWrite(led_g, HIGH); // Acende o LED verde
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    // Realiza leitura do sensor e avalia se é o maior valor encontrado para o verde
    leitura_ldr[1] = mediaLeituras(10);
    if (leitura_ldr[1] > color_cal[1]) {
      color_cal[1] = leitura_ldr[1];
    }
    
    digitalWrite(led_g, LOW); // Apaga o LED verde
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    digitalWrite(led_b, HIGH); // Acende o LED azul
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
    // Realiza leitura do sensor e avalia se é o maior valor encontrado para o azul
    leitura_ldr[2] = mediaLeituras(10);
    if (leitura_ldr[2] > color_cal[2]) {
      color_cal[2] = leitura_ldr[2];
    }
    
    digitalWrite(led_b, LOW); // Apaga o LED azul
    delay(100); // Aguarda 100ms para estabilizar o LDR
    
  }
  
  Serial.println("Remova o objeto");
  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

  // Início de calibração para valor mínimo de leitura do sensor
  black_cal[0] = 1023;
  black_cal[1] = 1023;
  black_cal[2] = 1023;
  
  Serial.println("Aproxime um objeto preto");
  
  while(analogRead(A0) > objeto_cal); // Aguarda a aproximação de um objeto
  delay(500); // Delay para estabilização do objeto na área do sensor
  
  Serial.println("Calibrando...");

  // São realizadas 10 medidas para encontrar o valor mínimo registrado pelo sensor
  for(int i = 0; i < 10; i++)
  {
    
    digitalWrite(led_r, HIGH);
    delay(100);
    
    leitura_ldr[0] = mediaLeituras(10);
    if (leitura_ldr[0] < black_cal[0]) {
      black_cal[0] = leitura_ldr[0];
    }
    
    digitalWrite(led_r, LOW);
    delay(100);
    
    digitalWrite(led_g, HIGH);
    delay(100);
    
    leitura_ldr[1] = mediaLeituras(10);
    if (leitura_ldr[1] < black_cal[1]) {
      black_cal[1] = leitura_ldr[1];
    }
    
    digitalWrite(led_g, LOW);
    delay(100);
    
    digitalWrite(led_b, HIGH);
    delay(100);
    
    leitura_ldr[2] = mediaLeituras(10);
    if (leitura_ldr[2] < black_cal[2]) {
      black_cal[2] = leitura_ldr[2];
    }
    
    digitalWrite(led_b, LOW);
    delay(100);
    
  }
  
  Serial.println("Remova o objeto");
  while(analogRead(ldr) < ambiente_cal); // Aguarda a remoção do objeto

  // Fim da calibração
  Serial.println("Calibracao finalizada");
  delay(1000);
  
  Serial.println('#'); // Envia caractere para informar fim da calibração
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
  
  digitalWrite(led_r, HIGH); // Acende o LED vermelho
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  leitura_ldr[0] = mediaLeituras(10); // Realiza a leitura do sensor
  
  digitalWrite(led_r, LOW); // Apaga o LED vermelho
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  digitalWrite(led_g, HIGH); // Acende o LED verde
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  leitura_ldr[1] = mediaLeituras(10); // Realiza a leitura do sensor
  
  digitalWrite(led_g, LOW); // // Apaga o LED verde
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  digitalWrite(led_b, HIGH); // Acende o LED azul
  delay(100); // Aguarda 100ms para o LDR estabilizar
  
  leitura_ldr[2] = mediaLeituras(10); // Realiza a leitura do sensor
  
  digitalWrite(led_b, LOW); // Apaga o LED azul
  
}

// Rotina para enviar o valor da cor lida, convertida para a escala RGB
void enviaCores() {

  // Converte o valor lido do sensor para a escala RGB (0 - 255)
  unsigned char red = constrain(map(leitura_ldr[0], black_cal[0], color_cal[0], 0, 255),0,255);
  unsigned char green = constrain(map(leitura_ldr[1], black_cal[1], color_cal[1], 0, 255),0,255);
  unsigned char blue = constrain(map(leitura_ldr[2], black_cal[2], color_cal[2], 0, 255),0,255);

  // Envia os valores convertidos para a porta serial
  Serial.print("R = ");
  Serial.println(red, DEC); 
  Serial.print("G = ");
  Serial.println(green, DEC);
  Serial.print("B = ");
  Serial.println(blue, DEC);
  
}
