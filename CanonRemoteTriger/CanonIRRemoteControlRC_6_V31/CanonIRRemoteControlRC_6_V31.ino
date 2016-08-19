/*
Canon IR Remote Trigger

My Remote Triger can control the Canon camera in different Operation Modes:
1) Manual Shutter Control: The camera must be set to Button mode (buy selecting a shuter speed slower thatn 30 secconds) so that pressing the Remote button once will open the shutter until the Remote button is pressed again.
2) Take pictiure: The camera must be set to 10 sec Delay mode. If the Remote button is pressed for less than 2 seconds, the camera instantly takes a picture.
3) Take 2s delayed Picture: The camera must be set to 10 sec Delay mode. If the Remote button is pressed for more than 2 secconds, the remote led will flash 200ms
if the Remote button is pressed again for less than 2 secconds, the camera will wait 2 secconds and then take a picture (allowing time for you to hide the Remote and pose for the picture!).
4) Execute a Pre-programmed Routine: The camera must be set to 10 sec Delay mode. If the Remote button is pressed for more than 2 secconds, the remote led will flash 200ms
if the Remote button is pressed again for more than 2 secconds, a software routine (that must be programmed inside the execRoutine() function) will be executed, controling the camera 
automaticaly until the end of the routine or the user press the Remote button for more than 2 secconds.


By Eduardo Simoes
22/03/2016
*/
const int buttonPin = 3;     // the number of the pushbutton pin

unsigned long previousMillis = 0;        // will store last time LED was updated

unsigned long interval = 1000;           // interval at which to blink (milliseconds)


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(buttonPin, INPUT);
}



void shutterON() {    // Pulse sequence to triger the camera Shutter Normaly
  for(int i=0; i<16; i++)  {
    digitalWrite(9, HIGH);   
    delayMicroseconds(11);   
    digitalWrite(9, LOW);   
    delayMicroseconds(11);  
  } 
  delayMicroseconds(7330);  
  for(int i=0; i<16; i++)  {
    digitalWrite(9, HIGH);  
    delayMicroseconds(11);  
    digitalWrite(9, LOW);   
    delayMicroseconds(11);  
  }  
}

void shutterDelayed() {    // Pulse sequence to triger the camera Shutter with 2 secconds delay
  for(int i=0; i<16; i++) { 
    digitalWrite(9, HIGH);
    delayMicroseconds(11);
    digitalWrite(9, LOW);
    delayMicroseconds(11);
  } 
  delayMicroseconds(5360); 
  for(int i=0; i<16; i++) { 
    digitalWrite(9, HIGH);
    delayMicroseconds(11);
    digitalWrite(9, LOW);
    delayMicroseconds(11);
  }
}
// Exemple of a Routine to be executed automatically by the camera!!
// 
void execRoutine() {
      interval = 5000;
      while(1) {  
          while(digitalRead(buttonPin)== HIGH){
              if (millis() - previousMillis >= interval) {
                  previousMillis = millis();
                  if (digitalRead(13) == HIGH)
                      digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                  else
                      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                  }
              } 
          
          if(digitalRead(buttonPin)== LOW) {
              digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
              int count = 0;  
              while ((digitalRead(buttonPin) == LOW) and (count < 200)) {
                    count++;
                    delay(10);
                    }
              if(count < 200) 
                  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
              else {
                  while (digitalRead(buttonPin) == LOW);            
                  return;        
                  }
              }                
           } 
       }

// the loop function runs over and over again forever
void loop() {
    interval = 1000;
    while(digitalRead(buttonPin)== HIGH){
        if (millis() - previousMillis >= interval) {
            previousMillis = millis();
            if (digitalRead(13) == HIGH)
                digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
            else
                digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
            }
        }  

        int count = 0;
        int fim = 0;  
        while ((digitalRead(buttonPin) == LOW) and (count < 200)) {
              count++;
              delay(10);
              }
        if(count < 200) 
            shutterON(); 
        else {
            interval = 200;
            while(digitalRead(buttonPin)== LOW){
                if (millis() - previousMillis >= interval) {
                    previousMillis = millis();
                    if (digitalRead(13) == HIGH)
                        digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                    else
                        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                    }
                }  
              while(!fim) {
                  while(digitalRead(buttonPin)== HIGH){
                      if (millis() - previousMillis >= interval) {
                          previousMillis = millis();
                          if (digitalRead(13) == HIGH)
                              digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                          else
                              digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                          }
                      }
                  if(digitalRead(buttonPin)== LOW) {
                      count = 0;  
                      digitalWrite(13, HIGH);    // turn the LED off by making the voltage LOW
                      while ((digitalRead(buttonPin) == LOW) and (count < 200)) {
                            count++;
                            delay(10);
                            }
                      if(count < 200) {
                          digitalWrite(13, HIGH);    // turn the LED off by making the voltage LOW
                          shutterDelayed();
                          fim = 1; 
                          }
                      else {
                          digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                          while (digitalRead(buttonPin) == LOW);
                          execRoutine();  
                          fim = 1;                          
                          }
                      }                
                  }
              }
          }    

