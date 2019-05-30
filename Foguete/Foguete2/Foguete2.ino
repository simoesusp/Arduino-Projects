// CONTROLE DO FOGUETE


const int CountDown = 3; // 5...4...3...2...1... FOGO!

const int LED = 13; 
const int MOTOR = 11; 

const int soundDetectedPin = 10; 
const int Barulho = LOW; // When there is a noise, becomes LOW !
const int Silencio = HIGH; // When there is a noise, becomes LOW 

const int TimeLigaMotor = 400;

const int tempoSoundBarulho = 30;
const int tempoSoundSilencio = 250; 

int countBarulho = 0;
int countSilencio = 0;
int contagem = CountDown + 1;

void setup ()
{
  Serial.begin(115200);  // O tempo da serial atrapalha muito na leitura!! Mantenha em 115200!!
  pinMode (soundDetectedPin, INPUT) ; 
  pinMode (LED, OUTPUT) ; 
  pinMode (MOTOR, OUTPUT) ; 
  
  digitalWrite(MOTOR, LOW); 
  digitalWrite(LED, LOW);  

  Serial.println("Comecou!!");  


}
void loop ()
{
   while(countBarulho < tempoSoundBarulho)
       {
       countSilencio = countSilencio + (digitalRead (soundDetectedPin) == Silencio);
       countBarulho = countBarulho + (digitalRead (soundDetectedPin) == Barulho);

       digitalWrite(LED, HIGH);  
       
       Serial.print("countB = ");  
       Serial.print(countBarulho); 
       Serial.print("    countS = ");  
       Serial.println(countSilencio);  

       }   
   countBarulho = 0;
   countSilencio = 0;   

   contagem--;
   Serial.print("Contagem = ");   
   Serial.println(contagem); 

   if(contagem == 0)
      {
     
      digitalWrite(LED, LOW);   
      digitalWrite(MOTOR, HIGH); 
      delay(TimeLigaMotor);
 
      Serial.println("Disparou...");
      digitalWrite(LED, HIGH);   
      digitalWrite(MOTOR, LOW);  
      delay(5000);  // So... It wont fire AGAIN!
      contagem = CountDown + 1;
      }
    
   while(countSilencio < tempoSoundSilencio)
       { 
       countSilencio = countSilencio + (digitalRead (soundDetectedPin) == Silencio);
       countBarulho = countBarulho + (digitalRead (soundDetectedPin) == Barulho); 
       if(countBarulho > 5)
          {
          countBarulho = 0;
          countSilencio = 0;      
          }
       digitalWrite(LED, LOW);  
       Serial.print("countB = ");  
       Serial.print(countBarulho); 
       Serial.print("    countS = ");  
       Serial.println(countSilencio);  
       }      
   countBarulho = 0;
   countSilencio = 0;
   Serial.println("Passou!!");  
  
}
