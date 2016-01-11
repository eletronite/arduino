/*
  Fade

  Este exemplo mostra como dimerizar (fade) um LED no pino 9
  usando a função analogWrite().

  A função analogWrite() usa PWM, portanto se
  você deseja trocar o pino que está usando, tenha
  certeza de que está utilizando outro pino capaz de
  realizar PWM. Na maioria dos Arduinos, os pinos
  PWM são identificados com o sinal "~", 
  por exemplo, ~3, ~5, ~6, ~9, ~10 e ~11.

  Este código de exemplo está em domínio público.
  
  modificado 11 Janeiro 2016
  por Ricardo Alcântara
*/

int led = 9;           // o pino PWM no qual o LED está conectado
int brilho = 0;    // quão brilhante o LED está
int quantidadeFade = 5;    // em quantos pontos dimerizar o LED

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// a função loop executa as instruções em sequência e repete para sempre:
void loop() {
  // seta o brilho do pino 9:
  analogWrite(led, brilho);

  // muda o brilho para a próxima passagem do loop:
  brilho = brilho + quantidadeFade;

  // reverte a direção da dimerização quando chega ao final: 
  if (brilho == 0 || brilho == 255) {
    quantidadeFade = -quantidadeFade ;
  }
  // aguarda 30 milisegundos para a percepção do efeito de dimerização
  delay(30);
}
