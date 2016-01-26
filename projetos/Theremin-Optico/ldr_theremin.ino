/*
  ldr_theremin
  
  Este código implementa um theremin óptico utilizando dois LDRs e um alto-falante.
  Um LDR é responsável por alterar a frequência do sinal da saída e o outro é
  responsável por alterar o volume da saída (variando o ciclo de trabalho do sinal
  de saída).
  
  Hardware Necessário:
   - 2x LDRs
   - 2x Resistores de 10k ohms
   - Resistor de 100 ohms
   - Alto-falante de 8 ohms
   - Fios
   
  mais informações: https://github.com/eletronite/arduino/tree/master/projetos/Theremin-Optico
  
  criado 22 Janeiro 2016
  por Ricardo Alcântara
  
  Licenciado por Eletronite (http://www.eletronite.com.br)
  
  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

// Definição de pinos
#define falante 8
#define ldr_volume A0
#define ldr_periodo A1

// Varíveis para armazenar a calibração do instrumento
int periodo_min, periodo_max;
int volume_min, volume_max;

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
 
  pinMode(falante, OUTPUT); // Configura pino do alto-falante como saída

  Serial.begin(9600); // Configura comunicação serial a 9600 bits por segundo
  Serial.println("Calibrando Theremin...");

  // Armazena leitura máxima dos LDRs (luminosidade do ambiente)
  periodo_max = mediaLeituras(10, ldr_periodo);
  volume_max = mediaLeituras(10, ldr_volume);
  
  Serial.println("Aproxime sua mao do LDR do periodo e envie qualquer caractere");

  Serial.flush();
  while(!Serial.available());

  Serial.println("Calibrando...");

  periodo_min = mediaLeituras(10, ldr_periodo); // Armazena leitura mínima para LDR do período

  Serial.println("Aproxime sua mao do LDR do volume e envie qualquer caractere");

  Serial.read();
  Serial.flush();
  while(!Serial.available());

  Serial.println("Calibrando...");

  volume_min = mediaLeituras(10, ldr_volume); // Armazena leitura mínima para LDR do volume

  Serial.println("Final da calibracao");
  Serial.println("Iniciando em 1 segundo");

  delay(1000);
  
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {

  // Chama rotina para definir a saída para o alto-falante
  somTheremin(analogRead(ldr_periodo), analogRead(ldr_volume));
  
}

// Rotina para definir a saída para o alto-falante
void somTheremin(int periodo, int duty) {

  // Ajusta variáveis para um intervalo de periodos e ciclos de trabalho
  periodo = constrain(map(periodo, periodo_min, periodo_max, 1, 500), 1, 500);
  duty = constrain(map(duty, volume_min, volume_max, 0, 70), 0, 70);

  // Executa a forma de onda com o período e ciclo de trabalho recebidos
  digitalWrite(falante, HIGH);
  delayMicroseconds(periodo*duty);
  digitalWrite(falante, LOW);
  delayMicroseconds(periodo*100 - periodo*duty);
  
}

// Rotina para realizar média nas leituras do sensor
int mediaLeituras(int vezes, int pino) {
  
  int leitura;
  int acumulador = 0;
  
  // Soma a leitura do sensor à variável acumulador pelo número de vezes
  for(int i = 0; i < vezes; i++){
    leitura = analogRead(pino);
    acumulador += leitura;
    delay(10);
  }
  
  // Calcula a média
  return((acumulador)/vezes);
  
}
