/*
  Blink
  Liga um LED por um segundo, e depois desliga por um segundo, repetidamente.

  A maioria dos Arduinos possui um LED soldado na placa que você pode controlar.
  No Uno e Leonardo, ele está conectado ao pino digital 13. Se você não sabe
  em qual pino o LED de sua placa está conectaco, cheque a documentação em
  http://www.arduino.cc

  Este código de exemplo está em domínio público.

  modificado 09 Janeiro 2016
  por Ricardo Alcântara
 */


// a função setup roda assim que você pressiona o botão de reset ou liga a placa
void setup() {
  // inicializa o pino digital 13 como saída.
  pinMode(13, OUTPUT);
}

// a função loop executa as instruções em sequência e repete para sempre
void loop() {
  digitalWrite(13, HIGH);   // liga o LED (HIGH/ALTO é o nível de tensão)
  delay(1000);              // aguarda um segundo
  digitalWrite(13, LOW);    // desliga o LED colocando a tensão em LOW (nível BAIXO)
  delay(1000);              // aguarda um segundo
}
