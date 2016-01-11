/*
  DigitalReadSerial
  Lê uma entrada digital no pino 2, imprime o resultado no monitor serial 

  Este código de exemplo está em domínio público.
  
  modificado 11 Janeiro 2016
  por Ricardo Alcântara
*/

// pino digital 2 possui um pushbutton conectado a ele. Atribua um nome a ele:
int pushButton = 2;

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
  // inicializa a comunicação serial em 9600 bits por segundo:
  Serial.begin(9600);
  // configura o pino do pushbutton como entrada:
  pinMode(pushButton, INPUT);
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {
  // lê o pino de entrada:
  int estadoBotao = digitalRead(pushButton);
  // imprime o estado do botão:
  Serial.println(estadoBotao);
  delay(1);        // aguarda entre leituras para garantir estabilidade
}


