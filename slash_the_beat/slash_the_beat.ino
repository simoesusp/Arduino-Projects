#include <NewPing.h>


#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 4000 // Maximum distance we want to ping for (in mili/10). Maximum sensor distance is rated at 400-500cm.


#define speakerPin 9

#define tempo 500

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
}

void loop() {

  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    uS = uS / US_ROUNDTRIP_CM; // Send ping, get ping time in microseconds (uS).

  
  if (uS > 200) {
    delay(tempo); // re
  } else if (uS <= 100 && uS > 90){
    playTone(1915, tempo); // c
  } else if (uS <= 90 && uS > 80){
    playTone(1700, tempo); // d
  } else if (uS <= 80 && uS > 70){
    playTone(1519, tempo); // e
  } else if (uS <= 70 && uS > 60){
    playTone(1432, tempo); // f
  } else if (uS <= 60 && uS > 50){
    playTone(1275, tempo); // g
  } else if (uS <= 50 && uS > 40){
    playTone(1136, tempo); // a
  } else if (uS <= 40 && uS > 30){
    playTone(1014, tempo); // b
  } else if (uS <= 30 && uS > 20){
    playTone(956, tempo); // C
  } else if (uS <= 20 && uS > 10){
    playTone(851, tempo); // D
  } else if (uS <= 10 && uS > 0){
    playTone(758, tempo); // E
  }

  // pause between notes
  //delay(tempo / 2); 
}
