/* Autor: Vitor Giovani Dellinocente */
#include <SoftwareSerial.h> // Biblioteca para que consiga emular uma porta serial no arduino

#define Tx 10 //Pino que envia os bits pela Serial.
#define Rx 11 //Pino que recebe os bits pela Serial.

char value;  // Valor que armazena o byte recebedo em um char (lembrando que, se voce envia pelo termino um numero que tenha mais de um digito, ele manda cada digito separadamente)
int value2;
int i = 0; // Contador para auxiliar na montagem dos bytes  
int flag; // Flag indicando que os bytes ja estao prontos para serem enviados.
int ledPin = 13; // Pino de saida
String bytes = ""; // String que recebera byte a byte e formará um numero completo, por exemplo, receberá 1, 2 e 3, e os transformara em 123.

SoftwareSerial serial(Rx, Tx); //criando um tipo SoftwareSerial, ou seja, estou emulando uma porta serial que nao existe em hardware (Rx recebe, Tx transmite)

// Essa funcao será executada uma unica vez no inicio da execucao
void setup() {
  Serial.begin(9600); //definindo a velocidade em que essa serial irá se comunicar com o terminal do pc
  serial.begin(9600); // definindo a velocidade em que essa serial irá receber ou transmitir dados entre arduinos.
}

//Essa funcao executará várias vezes apos a execucao de setup
void loop() {
  value2 = 0;
  flag = 0;
  bytes = "";
   // Laço para receber os bytes
  while (true) {
      if (serial.available()) {  //Há algum dado disponivel na serial?? (se sim, executa o if)  
         delay(500); // delay de 500 milisegundos para que nao seja perdido nenhum dado na serial (LEMBRE-SE, A EXECUCAO DA APLICACAO É MUITO MAIS RAPIDO QUE UMA PORTA SERIAL, TOME CUIDADO!!!)
         while (serial.available() > 0) { //A serial.available(), também guarda a quantidade de bytes que ainda há no buffer, ou seja esse while executará até nao ter mais nenhum dado faltando
            value = serial.read(); // Lê da Serial (LEMBRE QUE ESSA IMPLEMENTAÇÃO, FUNCIONA APENAS PARA O ENVIO DE 3 BYTES DE CADA VEZ, OU SEJA PARA MANDAR O VALOR 22, MANDE 022, E ASSIM POR DIANTE)
            /*Essa seção de if's encadeados é para que se monte o dado corretamente como um inteiro, recebendo byte a byte e montando o numero. Tive o problema de trabalhar com strings, ja que a porta serial nao passa um string completa, recomendo receber byte a byte e trandformar em inteiro, pois se nao, pode dar muito problema*/
            if(i == 0){
              value2 = ((value - 48) * 100) + value2; // Monta o terceito digito
            }else if(i == 1){
              value2 = ((value - 48) * 10) + value2; // Monta o segundo digito
            }else if(i == 2){
              value2 = (value - 48) + value2; // Monta o terceiro digito
              flag = 1; //Setar essa flag indica que o numero está pronto
            }
            i++;
         }
         i = 0;
         if (flag){
          break;
         }
      }
  }
   
  if(value2 < 30){ //  Se o valor respeitar essa condicao o led apaga, se nao ele acende
      digitalWrite(ledPin, LOW);
      value2 = 0;
      serial.write(value2); // envia uma mensagem para o arduino ligado ao pc indicando que o led apagou
  }else{
      digitalWrite(ledPin, HIGH);
      value2 = 1;
      serial.write(value2); //envia uma mensagem para o arduino ligado ao pc indicando que o led apgaou
  }
}
