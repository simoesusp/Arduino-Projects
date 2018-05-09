// CONTROLE DO FOGUETE

int LED = 13; 
int MOTOR = 11; 

int soundDetectedPin = 10; // Use Pin 10 as our Input
int soundDetectedVal = HIGH; // This is where we record our Sound Measurement
boolean bAlarm = false;

unsigned long lastSoundDetectTime; // Record the time that we measured a sound


int soundAlarmTime = 200; // Number of milli seconds to keep the sound alarm high


void setup ()
{
  Serial.begin(9600);  
  pinMode (soundDetectedPin, INPUT) ; // input from the Sound Detection Module
  pinMode (LED, OUTPUT) ; 
  pinMode (MOTOR, OUTPUT) ; 
  
  digitalWrite(LED, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(MOTOR, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(10000);               // wait for a second
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)


}
void loop ()
{
  soundDetectedVal = digitalRead (soundDetectedPin) ; // read the sound alarm time
  
  if (soundDetectedVal == LOW) // If we hear a sound
  {
  
    lastSoundDetectTime = millis(); // record the time of the sound alarm
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("LOUD, LOUD");
      bAlarm = true;
      digitalWrite(LED, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(MOTOR, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  }
  else
  {
    if( (millis()-lastSoundDetectTime) > soundAlarmTime  &&  bAlarm){
      Serial.println("quiet");
      bAlarm = false;
      digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(MOTOR, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100000);               // wait for a second

    }
  }
}
