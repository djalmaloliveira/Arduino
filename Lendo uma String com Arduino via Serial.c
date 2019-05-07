https://www.paulotrentin.com.br/programacao/dicas/lendo-uma-string-com-arduino-via-serial/


Lendo uma String com Arduino via Serial  Posted in Dicas By Paulo Marcos Trentin On setembro 16, 2014
O Problema
Uma dúvida muito comum quando estamos criando interfaces entre o Arduino e outros dispositivos externos via Serial, é como conseguir receber mais dados do que apenas um byte, exemplo ‘1’ ou ‘0’;

Imagine que você tem 5 LEDs conectados ao Arduino, e deseja ligá-los através de uma interface gráfica no computador, como o Processing. Como controlar separadamente esses 5 LEDs, de uma maneira simples?

A solução
Vamos imaginar que o Processing envie este padrão para trabalhar com um led: LEDX:STATUS. Para ligar o LED 1, o Processing envia esta informação ao Arduino: LED1:1, e para desligá-lo: LED1:0.

Simples de lidar não?

Código fonte

int led = 13;
  
void setup() { 
 pinMode(led, OUTPUT); 
 Serial.begin(9600);
}
  
/**
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Recebi: ");
  Serial.println(conteudo);
    
  return conteudo;
}
  
void loop() {
  // Se receber algo pela serial
  if (Serial.available() > 0){
    // Lê toda string recebida
    String recebido = leStringSerial();
      
    if (recebido == "LED1:1"){
      digitalWrite(led, HIGH);
    }
      
    if (recebido == "LED1:0"){
      digitalWrite(led, LOW);
    }
  }
}
Abra o monitor serial e faça testes escrevendo: LED1:1 e LED1:0 e veja que seu led do pino 13 do Arduino irá ligar e desligar de forma correspondente aos comandos.

Espero ter ajudado :)
