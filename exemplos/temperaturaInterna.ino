/*
  temperaturaInterna
  
  Lê o sensor de temperatura interna do Arduino e mostra o resultado em
  graus Celcius no monitor serial.
  
  modificado 29 Janeiro 2016
  por Ricardo Alcântara
*/

// a função setup roda assim que você pressiona o botão de reset ou liga a placa:
void setup()
{

  // Inicia a comunicação serial a 9600 bits por segundo
  Serial.begin(9600);

  Serial.println(F("Sensor de Temperatura Interna"));
  
}

void loop()
{
  
  // Imprime a temperatura em graus Celcius no monitor serial.
  Serial.println(leTemp(),1);
  delay(1000);
  
}

// Rotina de leitura da temperatura interna
double leTemp(void)
{
  
  unsigned int wADC;
  double t;

  // The internal temperature has to be used
  // com a referência de tensão interna de 1.1V

  // Seta a referência interna e mux.
  // Sensor de temperatura está no canal 8
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // habilita o ADC

  delay(20);            // aguarda as tensões estabilizarem.

  ADCSRA |= _BV(ADSC);  // Inicía a conversão

  // Aguarda o fim da conversão
  while (bit_is_set(ADCSRA,ADSC));

  // Lê o resultado da conversão.
  wADC = ADCW;

  // O offset de 324.31 pode estar errado. É somente uma indicação.
  t = (wADC - 324.31 ) / 1.22;

  // Retorna o valor de temperatura em graus Celcius.
  return (t);
  
}
