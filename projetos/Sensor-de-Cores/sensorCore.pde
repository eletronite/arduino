/*
  sensorCores
  
  Este código implementa uma interface visual para o sensor de cores 
  baseado em Arduino desenvolvido pela Eletronite.
  
  Recomenda-se a leitura e entendimento do código para Arduino antes 
  da leitura do presente código

  mais informações: 
  https://github.com/eletronite/arduino/tree/master/projetos/Sensor-de-Cores
  
  criado 22 Janeiro 2016
  por Ricardo Alcântara
  
  Licenciado por Eletronite (http://www.eletronite.com.br)

  Este código esta sob a licença CC BY-SA
  https://creativecommons.org/licenses/by-sa/4.0/legalcode
*/

import processing.serial.*; // Importa a biblioteca de comunicação serial

String buff = "";        // String para armazenar mensagens da porta serial
int r_val, g_val, b_val; // Variáveis para armazenar o valor das cores

boolean config = false;    // Variável para inicializar a configuração
boolean calibrado = false; // Variável para inicializar a calibração

Serial porta;

// a função setup roda somente uma vez assim que você inicializa o programa:
void setup() { 

  size(900,600); // Define o tamanho da tela como 900x600

  porta = new Serial(this, "COM7", 9600); // Inicializa a porta serial
  //Lembre-se de trocar COM7 com a porta que o seu Arduino está utilizando.
  
  porta.bufferUntil('\n'); // Configura comunicação serial para gerar interrupção sempre que receber comando de nova linha
  
  frameRate(2); // Define atualização de quadros pra 2 frames por segundo para animação introdutória
} 

// a função draw roda repetidamente, realizando desenhos a cada novo ciclo:
void draw() { 
  
  // Executa animação de introdução durante os 4 primeiros segundos de execução do programa
  if(millis() < 4000 && config == false)
  {
    
    background(random(0,200),random(0,200),random(0,200)); // Define cor de fundo aleatória
    
    // Escreve texto de introdução
    textSize(30);
    textAlign(CENTER);
    text("Sensor de Cores",450,280);
    textSize(16);
    textAlign(CENTER);
    text("Versão 1.0",450,300);
    textSize(12);
    textAlign(RIGHT);
    text("Eletronite 2016",895,595);
    
  } else {
    
    // Verifica se sensor já foi configurado
    if(config == false)
    {
      
      configuraSensor(); // Chama rotina de configuração do sensor
      
    } else {
      
      background(r_val,g_val,b_val); // Define cor de fundo de acordo com os valores recebidos
      
      // Verifica se sensor já foi calibrado
      if(calibrado) {
        
        color c = color(r_val, g_val, b_val);  // Cria uma variável de cor
        float brilho = brightness(c); // Verifica o brilho correspondente à cor
        
        // Altera a cor da fonte de acordo com o brilho da cor de fundo
        if(brilho < 127)
        {
          
          fill(255); // Texto branco
          
        } else {
          
          fill(0); // Texto preto
          
        }
        
        // Escreve as informações da cor na tela
        textSize(18);
        textAlign(LEFT);
        text("R = "+r_val,800,450);
        text("G = "+g_val,800,470);
        text("B = "+b_val,800,490);
        
        // Escreve as informações do programa
        textSize(12);
        textAlign(RIGHT);
        text("Eletronite 2016",895,595);
        textAlign(LEFT);
        text("Sensor de Cores V1.0",5,595);
        
      } else {
        
        calibraSensor(); // Chama rotina de calibração do sensor
        
      }
    }
  } 
} 

// Rotina de calibração do sensor
void calibraSensor() {
  
  //  Verifica se a calibração foi finalizada
  if(buff.indexOf("#") >= 0)
  {
    
    calibrado = true; // Seta variável indicando sensor já calibrado
    
  } else {
    
    // Escreve as instruções de calibração
    textSize(24);
    textAlign(CENTER);
    text(buff,450,300);
    
    // Escreve as informações do programa
    textSize(12);
    textAlign(RIGHT);
    text("Eletronite 2016",895,595);
    textAlign(LEFT);
    text("Sensor de Cores V1.0",5,595);
    
  }
  
}

// Rotina de configuração do sensor
void configuraSensor() {
  
  frameRate(60); // Altera a taxa de frames para maior atualização da tela
  
  porta.write(0); // Inicia comunicação com Arduino (handshake)
  
  config = true; // Seta variável indicando sensor já configurado
  
}

// Rotina de interrupção da comunicação serial
void serialEvent(Serial porta) { 
  
  // Lê string recebida até o comando de nova linha
  buff = porta.readStringUntil('\n');
  
  // Verifica se sensor já foi calibrado
  if(calibrado) {
    
    String val; // String para armazenar valor temporário da leitura do sensor
    
    int r_pos = buff.indexOf("R"); // Verifica se a letra R existe na string
    int g_pos = buff.indexOf("G"); // Verifica se a letra G existe na string
    int b_pos = buff.indexOf("B"); // Verifica se a letra B existe na string
  
    // Verifica se a leitura do valor vermelho foi recebida
    if(r_pos >=0){
      
      val = buff.substring(r_pos+3); // Separa somente os números recebidos
      r_val = Integer.parseInt(val.trim()); // Converte os números para um valor inteiro
      
    }    
    
    // Verifica se a leitura do valor verde foi recebida
    if(g_pos >=0){
      
      val = buff.substring(g_pos+3); // Separa somente os números recebidos
      g_val = Integer.parseInt(val.trim()); // Converte os números para um valor inteiro
      
    }
    
    // Verifica se a leitura do valor azul foi recebida
    if(b_pos >=0){
      
      val = buff.substring(b_pos+3); // Separa somente os números recebidos
      b_val = Integer.parseInt(val.trim()); // Converte os números para um valor inteiro
      
    }
  
    buff = ""; // Limpa a string buff
    
  }
  
} 
