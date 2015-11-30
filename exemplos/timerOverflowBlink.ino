/* 
 timerOverflowBlink
 
 Neste exemplo piscamos um LED, conectado ao pino 13, utilizando o Timer1
 no modo normal, de modo a deixar o bloco loop() livre para outras atividades.

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
  pinMode(pinoLED, OUTPUT);
 
  // inicialização do timer1
  noInterrupts();         // desbilita todas as interrupções
  TCCR1A = 0;             // reseta os registros de controle para configuração
  TCCR1B = 0;
 
  TCNT1 = 34286;            // pré carrega contador 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);    // pré escala de 256
  TIMSK1 |= (1 << TOIE1);   // habilita interrupção de overflow do contador
  interrupts();           // habilita todas as interrupções
}
 
ISR(TIMER1_OVF_vect)        // rotina de serviço de interrupção
{
  TCNT1 = 34286;            // pré carrega contador
  digitalWrite(pinoLED, digitalRead(pinoLED) ^ 1); // pisca o LED
}
 
void loop()
{
  // aqui você pode realizar outras atividades
}
