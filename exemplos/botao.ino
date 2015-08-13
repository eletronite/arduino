/*
  Botao

 Liga e desliga um diodo emissor de luz(LED) conectado ao pino
 digital 13, quando se pressiona um botão ligado ao pino 2.


 O circuito:
 * LED conectado do pino 13 para o terra
 * Chave tactil conectada do pino 2 para +5V
 * Resistor de 10K conectado do pino 2 para o terra

 * Nota: na maioria dos Arduinos já existe um LED na placa
 ligado ao pino 13.


 criado 2005
 por DojoDave <http://www.0j0.org>
 modificado 12 Agosto 2015
 por Ricardo Alcântara

 Este código de exemplo está em domínio público.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constantes não mudam. Eles são usadas aqui para 
// setar o número dos pinos:
const int pinoBotao = 2;    // o número do pino da chave tactil 
const int pinoLED = 13;     // o número do pino do LED 

// variáveis vão mudar: 
int estadoBotao = 0;        // variável para ler o estado do botão

void setup() {
  // inicializa o pino do LED como uma saída: 
  pinMode(pinoLED, OUTPUT); 
  // inicializa o pino do botão como uma entrada: 
  pinMode(pinoBotao, INPUT); 
}

void loop() {
  // lê o estado do botão:
  estadoBotao = digitalRead(pinoBotao);

  // checa se o botão está pressionado.
  // se está, o estadoBotao está em nível alto (HIGH):
  if (estadoBotao == HIGH) {
    // liga o LED:
    digitalWrite(pinoLED, HIGH);
  }
  else {
    // desliga o LED:
    digitalWrite(pinoLED, LOW);
  }
}
