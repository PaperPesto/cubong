// Test Tensore

#include <Cubong.h>

Cubong flashino(7,6,5);

int analogInput = A0;
int ritardo;

void setup()

{

  Serial.begin(9600);

  flashino.fillPiano(0);
  flashino.fillPiano(1);
  flashino.fillPiano(2);
  flashino.fillPiano(3);
  flashino.fillPiano(4);

}


void loop()

  {
  
  
  ritardo = (float)analogRead(analogInput) / (float)1023 * 500;
  
  Serial.println(flashino.accendiCubo(ritardo));
  flashino.spengiCubo();  delay(ritardo);
  //Serial.println(flashino.lampeggiaCubo(ritardo,1));
  
 
   
  }
  

