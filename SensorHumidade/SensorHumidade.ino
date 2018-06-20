

// these constants describe the pins. They won't change:
const int sensor = A1;                  // z-axis (only on 3-axis models)
int agua;

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);
  
  digitalWrite(13, LOW); 
}

void loop()
{
  
  agua = analogRead(sensor);
  // print the sensor values:
  Serial.print("Leitura = ");
  // print a tab between values:
  Serial.print("\t");
  Serial.print(agua);
  // print a tab between values:
  Serial.print("\t");
  
  if(agua > 1000)  Serial.print("Seco");
  else Serial.print("Molhado");
  
  Serial.println();
  // delay before next reading:
  delay(500);
}
