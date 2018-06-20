

// these constants describe the pins. They won't change:
const int botao = 7;                  
const int led = 13;                 

int ligado;

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);
    pinMode(led, OUTPUT);   
    pinMode(botao, INPUT);     
  

  digitalWrite(led, LOW); 
}

void loop()
{
  
  ligado = digitalRead(botao);
  Serial.print("Botao = ");
  // print a tab between values:
  Serial.print("\t");
  Serial.print(ligado);
  // print a tab between values:
  Serial.print("\t");
  
  if(ligado == 1)  Serial.print("Ligado");
  else Serial.print("Desligado");
  
  Serial.println();
  // delay before next reading:
  delay(500);
}
