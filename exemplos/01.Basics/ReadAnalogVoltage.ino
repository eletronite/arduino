/*
  ReadAnalogVoltage
  
  Lê uma entrada analógica no pino A0, converte seu valor para tensõa, e imprime o resultado no monitor serial.
  Representação gráfica está disponível utilizando o plotter serial (Ferramentas > Plotter Serial)
  Conecte o pino central de um potênciometro ao pino A0, e os pinos de fora a 5V (VCC) e terra (GND).

  Este código de exemplo está em domínio público.
  
  modificado 11 Janeiro 2016
  por Ricardo Alcântara
*/

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
  // inicializa a comunicação serial em 9600 bits por segundo:
  Serial.begin(9600);
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {
  // lê o valor no pino analógico A0:
  int valorSensor = analogRead(A0);
  // Converte a leitura analógica (que vai de 0 - 1023) para uma tensão (0 - 5V):
  float tensao = valorSensor * (5.0 / 1023.0);
  // imprime o valor que foi lido:
  Serial.println(tensao);
}
