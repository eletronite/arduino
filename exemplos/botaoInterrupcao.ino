/*
  botaoInterrupcao

 Liga e desliga um diodo emissor de luz(LED) conectado ao pino
 digital 13, quando se pressiona um botão ligado ao pino 2.


 O circuito:
 * LED conectado do pino 13 para o terra
 * Chave tactil conectada do pino 2 para +5V
 * Resistor de 10K conectado do pino 2 para o terra

 * Nota: na maioria dos Arduinos já existe um LED na placa
 ligado ao pino 13.


 criado 2015
 por Ricardo Alcântara

 Este código de exemplo está em domínio público.

 https://github.com/eletronite/Arduino
 */

// constantes não mudam. Eles são usadas aqui para 
// setar o número dos pinos:
const int pinoBotao = 2;    // o número do pino da chave tactil
const int pinoLED = 13;     // o número do pino do LED

// variáveis vão mudar: 
volatile int estadoBotao = 0;        // variável para ler o estado do botão

void setup() { 
  // inicializa o pino do LED como uma saída: 
  pinMode(pinoLED, OUTPUT); 
  // inicializa o pino do botão como uma entrada: 
  pinMode(pinoBotao, INPUT); 
  // atribui uma interrupção ao vetor ISR 
  attachInterrupt(0, pino_ISR, CHANGE); 
} 

void loop() { 
  // Nada aqui! 
} 

void pino_ISR() { 
  // lê o estado do botão:
  estadoBotao = digitalRead(pinoBotao); 
  // liga ou desliga o LED de acordo com o estado do botão
  digitalWrite(pinoLED, estadoBotao); 
}
