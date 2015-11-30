/* 
 timerBlink
 
 Neste exemplo piscamos um LED, conectado ao pino 13, utilizando o Timer1
 no modo CTC, de modo a deixar o bloco loop() livre para outras atividades.

 O circuito:
 * LED conectado do pino 13 para o terra

 * Nota: na maioria dos Arduinos já existe um LED na placa
 ligado ao pino 13.

 criado 2015
 por Ricardo Alcântara

 Este código de exemplo está em domínio público.
 
 https://github.com/eletronite/Arduino
*/
 
#define pinoLED 13
 
void setup()
{
  pinMode(pinoLED, OUTPUT); // define o pino 13 como saída
  
  // inicialização do timer1
  noInterrupts();         // desabilita todas as interrupções
  TCCR1A = 0;             // reseta os registros de controle para configuração
  TCCR1B = 0;
  TCNT1  = 0;             // zera o valor do contador
 
  OCR1A = 31250;          // registrador de comparação por igualdade 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // Seta o modo CTC
  TCCR1B |= (1 << CS12);    // pré escala de 256
  TIMSK1 |= (1 << OCIE1A);  // habilita a interrupção de comparação do timer
  interrupts();           // habilita todas as interrupções
}
 
ISR(TIMER1_COMPA_vect)          // rotina de serviço de interrupção
{
  digitalWrite(pinoLED, digitalRead(pinoLED) ^ 1);   // pisca o LED
}
 
void loop()
{
  // aqui você pode realizar outras atividades
}
