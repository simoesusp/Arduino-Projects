#include <SoftwareSerial.h>
#include <PWM.h>
#include <NewPing.h>

//A -> RIGHT
//B -> FRONT
//C -> LEFT
#define ECHO_PINA     2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PINB     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PINC     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PINA  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PINB  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PINC  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SPEED 3

NewPing sonarA(TRIGGER_PINA, ECHO_PINA, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarB(TRIGGER_PINB, ECHO_PINB, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarC(TRIGGER_PINC, ECHO_PINC, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int uS;

long durationA, distanceA;
long durationB, distanceB;
long durationC, distanceC;

int Sensor1, Sensor2, Sensor3, M1, M2;

int targetVelocidade = 0;
float L=0;
float R=0;
int count = 0;

int LED = 13;

int M1PWM = 9;
int M1DirA = 8;
int M1DirB = 6;

int M2PWM = 10;
int M2DirA = 7;
int M2DirB = 5;

int32_t frequency = 50;
bool successM1 = false;
bool successM2 = false;

SoftwareSerial mySerial(11, 12); // RX, TX

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(M1DirA, OUTPUT);
  pinMode(M1DirB, OUTPUT);
  pinMode(M2DirA, OUTPUT);
  pinMode(M2DirB, OUTPUT);
   
  digitalWrite(LED, LOW);    
  digitalWrite(M1DirA, HIGH); 
  digitalWrite(M1DirB, LOW);
  digitalWrite(M2DirA, HIGH); 
  digitalWrite(M2DirB, LOW);
  
  InitTimersSafe();
  successM1 = SetPinFrequencySafe(M1PWM, frequency);
  successM2 = SetPinFrequencySafe(M2PWM, frequency);

  if(successM1 && successM2) 
    digitalWrite(LED, HIGH);    
  
  pwmWrite(M1PWM, 0);
  pwmWrite(M2PWM, 0);
  
  Serial.begin(9600);
  mySerial.begin(9600);
} 
 
void loop() {
   float distLeft, distRight, distFront;
   bool obstacle_left = false;
   bool obstacle_right = false;
        
 
          L = SPEED;
          R = SPEED;

          //Obstacle left. Turn right.
          uS = sonarA.ping(); // Send ping, get ping time in microseconds (uS).
          distLeft = uS / US_ROUNDTRIP_CM; // Convert ping time to distance in cm and print result (0 = outside set distance range)
          if (distLeft < 100 && distLeft >0) // Se contador chegar a 1 seg stop robot
                        {
                         //R = (1.0*SPEED) * distLeft/(1.0*MAX_DISTANCE); 
                         R = 0;
                         L = SPEED;
                         //obstacle_left = true;
                        }

          //Obstacle right. Turn left.
          uS = sonarC.ping(); // Send ping, get ping time in microseconds (uS).
          distRight = uS / US_ROUNDTRIP_CM; // Convert ping time to distance in cm and print result (0 = outside set distance range)
          if (distRight < 100 && distRight >0) // Se contador chegar a 1 seg stop robot
                        {
                         //L = (1.0*SPEED) * distRight/(1.0*MAX_DISTANCE);
                         L = 0;
                         R = SPEED;
                         //obstacle_right = true;
                        }
          
          //Obstacle front.
          uS = sonarB.ping(); // Send ping, get ping time in microseconds (uS).
          //if(uS > 0) digitalWrite(LED, LOW);
          distFront = uS / US_ROUNDTRIP_CM; // Convert ping time to distance in cm and print result (0 = outside set distance range)
          if (distFront < 100 && uS >0) // Se contador chegar a 1 seg stop robot
                        {
                          R = 0;
                          L = SPEED;
                        }
                        
          int sL = 51*L, sR = 51*R;
          pwmWrite(M1PWM, sR);
          pwmWrite(M2PWM, sL);

  //delay(20);

Serial.print("\nR= ");
Serial.write((int)R+48);
Serial.print("L= ");
Serial.write((int)L+48);

} 

