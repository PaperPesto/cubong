// Test Tensore

#include <Cubong.h>

Cubong lettere(7,6,5);

int analogInput = A0;
int ritardo;

int durata;


void setup()

{

  Serial.begin(9600);
  durata = 50;
 

}


void loop()

  {
  int i;
  ritardo = (float)analogRead(analogInput) / (float)1023 * 4;
  
  
  for(i=0;i<20;i++) 
  {
    lettere.letteraM(ritardo, durata);
    ritardo = (float)analogRead(analogInput) / (float)1023 * 4;
  }
  
  for(i=0;i<20;i++) {
    lettere.letteraI(ritardo, durata);
    ritardo = (float)analogRead(analogInput) / (float)1023 * 4;
  }
  
  for(i=0;i<20;i++) {
    lettere.letteraS(ritardo, durata);
    ritardo = (float)analogRead(analogInput) / (float)1023 * 4;
  }
  
  for(i=0;i<20;i++) {
    lettere.letteraS(ritardo, durata);
    ritardo = (float)analogRead(analogInput) / (float)1023 * 4;
  }

  
  lettere.azzeraTensore();
  lettere.fillPiano(0);
  lettere.fillPiano(1);
  lettere.fillPiano(2);
  lettere.fillPiano(3);
  lettere.fillPiano(4);
  
  for(i=0;i<10;i++)
  {
  lettere.lampeggiaCubo(millis()%3*20, 5);
  }
   
  }
  

