// Sfoglia piani input

#include <Cubong.h>

int analogInput = A0;
int ritardo;

Cubong cubiano(7,6,5);

void setup()

{

  Serial.begin(9600);
  
}


void loop()

  

  {
 
  int k; 
  for(k=0;k<5;k++)  
    {
    cubiano.piano(k);
    ritardo = (float)analogRead(analogInput) / (float)1023 * 500;
    delay(ritardo);
    }
    
}
  

