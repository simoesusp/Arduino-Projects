// CONTROLE DO FOGUETE

int LED = 13; 
int MOTOR = 11; 

int soundDetectedPin = 10; 
int soundDetectedVal = HIGH; // When there is a noise, becomes LOW !



int soundAlarmTime = 200; 


void setup ()
{
  Serial.begin(9600);  
  pinMode (soundDetectedPin, INPUT) ; 
  pinMode (LED, OUTPUT) ; 
  pinMode (MOTOR, OUTPUT) ; 
  
  digitalWrite(LED, LOW);   
  digitalWrite(MOTOR, LOW); 
  delay(10000);             
  digitalWrite(LED, HIGH);  


}
void loop ()
{
  soundDetectedVal = digitalRead (soundDetectedPin) ; 
  
  if (soundDetectedVal == LOW) 
    {  
      Serial.println("Fogo!!");
      delay(25);
      digitalWrite(LED, LOW);   
      digitalWrite(MOTOR, HIGH); 
      delay(soundAlarmTime);
 
      Serial.println("Disparou...");
      digitalWrite(LED, HIGH);   
      digitalWrite(MOTOR, LOW);  
  delay(90000);  // So... It wont fire AGAIN!

    }
  
}
