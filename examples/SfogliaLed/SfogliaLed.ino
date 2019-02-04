// Sfoglia led

#include <Cubong.h>

Cubong cubingolo(7,6,5,4);

void setup()

{

  Serial.begin(9600);
  
}

int i,j,k;

void loop()

{
  for(k=0;k<5;k++)
    {
    for(j=0;j<5;j++)
      {
      for(i=0;i<5;i++)
        {
  
        cubingolo.led(i,j,k);
        delay(50);
        }
      }
    }
}
  



