#include <SoftwareSerial.h>
#include <PWM.h>

int targetVelocidade = 0;
int L=0;
int R=0;
int count = 0;

int LED = 13;

int M1PWM = 9;
int M1DirA = 7;

int M2PWM = 10;
int M2DirA = 6;

int32_t frequency = 50;
bool successM1 = false;
bool successM2 = false;

SoftwareSerial mySerial(11, 12); // RX, TX

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(M1DirA, OUTPUT);
  pinMode(M2DirA, OUTPUT);
  
  digitalWrite(LED, LOW);    
  digitalWrite(M1DirA, LOW); 
  digitalWrite(M2DirA, LOW);

  InitTimersSafe();
  successM1 = SetPinFrequencySafe(M1PWM, frequency);
  successM2 = SetPinFrequencySafe(M2PWM, frequency);

  if(successM1 && successM2) 
    digitalWrite(LED, HIGH);    
  
  pwmWrite(M1PWM, 90);
  pwmWrite(M2PWM, 90);
  
  Serial.begin(9600);
  mySerial.begin(9600);
} 
 
void loop() {
  
  count++;
  if (count > 1000) // Se contador chegar a 1 seg stop robot
        {
         pwmWrite(M1PWM, 0);
         pwmWrite(M2PWM, 0); 
         count = 0;
        }
        
  delay(1);
  
  if (mySerial.available()) {
          //delay(10);
          targetVelocidade = (mySerial.read());
          
          L = targetVelocidade/16;
          R = targetVelocidade - L*16;
        
          if(((L == R) || (L==R+1) || (L==R+2) || (L==R+3) || (L==R+4) || (L==R+5)) || ((R==L+1) || (R==L+2) || (R==L+3) || (R==L+4) || (R==L+5))) 
              {
              pwmWrite(M1PWM, (30*L));
              pwmWrite(M2PWM, (30*R));
              
              count = 0;  // Se recebeu comando valido, Zera contador
              }

      } 
      
  if (Serial.available() > 0) {
          delay(10);
          targetVelocidade = (Serial.read());
          Serial.write(targetVelocidade);
          
          L = targetVelocidade/16;
          R = targetVelocidade - L*16;
          
          pwmWrite(M1PWM, (30*L));
          pwmWrite(M2PWM, (30*R));
          
          count = 0;
      }       

} 

