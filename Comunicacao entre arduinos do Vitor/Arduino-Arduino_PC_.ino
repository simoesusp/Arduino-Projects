/* Autor: Vitor Giovani Dellinocente */

#include <SoftwareSerial.h> // Biblioteca para que consiga emular uma porta serial no arduino

#define Tx 10  //Pino que envia os bits pela Serial.
#define Rx 11 //Pino que recebe os bits pela Serial.

int flag; // Flag indicando que os bytes ja estao prontos para serem enviados.
int i = 0; // Contador para auxiliar na montagem dos bytes  
char value = 0; // Valor que armazena o byte recebedo em um char (lembrando que, se voce envia pelo termino um numero que tenha mais de um digito, ele manda cada digito separadamente)
int n = 0; // Valor para saber se o led esta ligado ou desligado

String bytes = ""; // String que recebera byte a byte e formará um numero completo, por exemplo, receberá 1, 2 e 3, e os transformara em 123.

SoftwareSerial serial(Rx, Tx); //criando um tipo SoftwareSerial, ou seja, estou emulando uma porta serial que nao existe em hardware (Rx recebe, Tx transmite)

// Essa funcao será executada uma unica vez no inicio da execucao
void setup() {
  Serial.begin(9600); //definindo a velocidade em que essa serial irá se comunicar com o terminal do pc
  serial.begin(9600); // definindo a velocidade em que essa serial irá receber ou transmitir dados entre arduinos.

  Serial.flush(); // Limpa algum dado que esteja na porta serial
  serial.flush(); // Limpa algum dado que esteja na porta serial

}

//Essa funcao executará várias vezes apos a execucao de setup
void loop() {
  int i = 0;
  flag = 0;
  // Laço para receber os bytes
   while (true) {
      if (Serial.available()) { //Há algum dado disponivel na serial?? (se sim, executa o if)  
         delay(100); // delay de 100 milisegundos para que nao seja perdido nenhum dado na serial (LEMBRE-SE, A EXECUCAO DA APLICACAO É MUITO MAIS RAPIDO QUE UMA PORTA SERIAL, TOME CUIDADO!!!)
         while (Serial.available() > 0) { //A serial.available(), também guarda a quantidade de bytes que ainda há no buffer, ou seja esse while executará até nao ter mais nenhum dado faltando 
            value = Serial.read() ; // Lê da Serial (LEMBRE QUE ESSA IMPLEMENTAÇÃO, FUNCIONA APENAS PARA O ENVIO DE 3 BYTES DE CADA VEZ, OU SEJA PARA MANDAR O VALOR 22, MANDE 022, E ASSIM POR DIANTE)
            bytes.concat(value); // Concatena numa string, cada byte lido individualmente.
         }
         flag = 1; // Flag recebe um indicando que o dado ja foi lido
      }
      if(flag){
        Serial.println(bytes); // Printa na tela os bytes lidos e concatenados, para que se saiba que estes foram lidos corretamente
        for(i = 0;i<bytes.length();i++){
          serial.write(bytes[i]); // Passa byte a byte através da serial para o outro arduino conectado neste em que esse codigo esta sendo executado
        }  
        flag = 0; // Reinicializa a flag
        bytes = ""; // Reinicializa a string de bytes
        while(true){
          if(serial.available()){ //Se o segundo arduino ja terminou de processar os dados, ele enviara via serial a resposta
            n = serial.read(); // Lê se a resposta da Serial
            break;
          }
        }
        if(n == 1){Serial.println("on");} //Caso a resposta seja 1, o led liga
        else {Serial.println("off");} // Caso contrario ele desliga
      }
   }
}
