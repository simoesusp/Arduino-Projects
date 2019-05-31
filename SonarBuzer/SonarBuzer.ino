// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second. 
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PINA    11  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define ECHO_PINB     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
unsigned int uS;

int LED = 13;
int BUZ = 9;

#define MAX_DISTANCE 350 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarA(TRIGGER_PIN, ECHO_PINA, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//NewPing sonarB(TRIGGER_PIN, ECHO_PINB, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZ, OUTPUT);
  
  digitalWrite(LED, LOW);    
  digitalWrite(BUZ, LOW); 
  
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(200);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  uS = sonarA.ping() / US_ROUNDTRIP_CM; // Send ping, get ping time in microseconds (uS).
  Serial.print("PingA: ");
  Serial.print(uS); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm      ");
  
  if (uS < 50 && uS >0) // Se contador chegar a 1 seg stop robot
      {
      digitalWrite(LED, HIGH);    
      digitalWrite(BUZ, HIGH); 
      delay(10);
      digitalWrite(BUZ, LOW); 
      delay(10);
      digitalWrite(BUZ, HIGH); 
      delay(10);
      digitalWrite(BUZ, LOW); 
      delay(10);
      digitalWrite(BUZ, HIGH); 
      delay(10);
      digitalWrite(BUZ, LOW); 
      delay(10);
      digitalWrite(BUZ, HIGH); 
      delay(10);
      digitalWrite(BUZ, LOW); 
      delay(10);
      }
  else if (uS < 100 && uS >=50) // Se contador chegar a 1 seg stop robot
      {
      digitalWrite(LED, HIGH);    
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      }
  else if (uS < 200 && uS >=100) // Se contador chegar a 1 seg stop robot
      {
      digitalWrite(LED, HIGH);    
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      digitalWrite(BUZ, HIGH); 
      delay(40);
      digitalWrite(BUZ, LOW); 
      delay(40);
      }
  else if (uS < 300 && uS >=200) // Se contador chegar a 1 seg stop robot
      {
      digitalWrite(LED, HIGH);    
      digitalWrite(BUZ, HIGH); 
      delay(80);
      digitalWrite(BUZ, LOW); 
      delay(80);
      digitalWrite(BUZ, HIGH); 
      delay(80);
      digitalWrite(BUZ, LOW); 
      delay(80);
      digitalWrite(BUZ, HIGH); 
      delay(80);
      digitalWrite(BUZ, LOW); 
      delay(80);
      digitalWrite(BUZ, HIGH); 
      delay(80);
      digitalWrite(BUZ, LOW); 
      delay(80);
      }
  else
      {
      digitalWrite(LED, LOW);    
      digitalWrite(BUZ, LOW); 
      }

  
/*  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  uS = sonarB.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("PingB: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
*/  
}
