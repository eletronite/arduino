/*
  sensorToque
  
  Este código implementa um sensor de toque simples utilizando papel
  alumínio conectado ao pino 4 através de um resistor de 1M ohm e
  ao pino 8 através de um fio.
  
  Qualquer outra superfície metálica pode ser utilizada no lugar do
  pape alumínio.
  
  O sensor funciona medindo o tempo de carga do capacitor formado pelo 
  papel alumínio e suas interações com o ambiente e o circuito, cuja 
  capacitância vista por um dos pinos do arduino varia com a aproximação
  de um dedo ou outros objetos.

  Hardware Necessário:
   - Papel Alumínio
   - Resistor de 1M ohm
   - Fios
  mais informações: https://github.com/eletronite/arduino/tree/master/projetos/Sensor-de-Toque
  
  criado 20 Julho 2016
  por Ricardo Alcântara
  Licenciado por Eletronite (http://www.eletronite.com.br)
  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

// Definição de pinos
int carrega = 4;
int sense = 8;
int ledPin = 13;

// Variável para armazenar o valor lido do sensor
unsigned int valor;

// A função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
  
  // Define o modo dos pinos
  pinMode(ledPin, OUTPUT);
  pinMode(carrega, OUTPUT);
  pinMode(sense, INPUT);

  // Inicializa a comunicação serial em 9600 bits por segundo:
  Serial.begin(9600);
}

// A função loop executa as instruções em sequência e repete para sempre:
void loop() {

  // Lê o valor do sensor
  valor = sensorCapacitivo(30);
  
  // Imprime o valor no monitor seial
  Serial.println(valor);
  
  // Se o valor for maior que um dado threshold acende o led
  if (valor > 50) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(100); // Delay para não sobrecarregar o monitor serial
}

// Função para leitura do sensor
// Executa pelo número de amostras passado e retorna o valor lido
unsigned int sensorCapacitivo(unsigned char amostras) {

  unsigned long sum = 0;
  unsigned long tempo = 0;
  
  // Executa função 'amostras' vezes
  for (int i = 0; i < amostras; i++) {
    digitalWrite(carrega, LOW);
    
    // Coloca o pino do sensor como saída para garantir nível baixo
    pinMode(sense, OUTPUT);
    digitalWrite(sense, LOW);
    delayMicroseconds(10); // Delay para estabilidade
    
    // Atera o modo do pino do sensor para entrada
    pinMode(sense, INPUT);
    
    // Inicia carga do sensor
    digitalWrite(carrega, HIGH);
    
    // Aguarda pino atingir nível alto (aproximadamente 2.5V)
    while (digitalRead(sense) == LOW) {
      tempo++; // Acumula tempo para atingir nível alto
    }
    
    // Acumula valor para média
    sum += tempo;
  }
  
  // Realiza média e retorna valor lido
  return (unsigned int)sum/amostras;
}
