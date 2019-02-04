// Sfoglia piani

#include <Cubong.h>

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
    cubiano.piano(k); delay(50);
    }

    
}
  

