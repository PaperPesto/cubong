//Riempi Cubo

/*
Dimostra l'utilizzo di Tensore[][][]
nella libreria
*/

#include <Cubong.h>

Cubong cuborana(7,6,5,4);

void setup()
{

Serial.begin(9600);
}

void loop()

{
  int i,j,k;
  
  for(k=0;k<5;k++)
    {	
    for(i=0;i<5;i++)  
      {
      for(j=0;j<5;j++)  
        {
        cuborana.add(i,j,k);
        cuborana.stampaPiano(k);
        delay(100);
        }
      }
    cuborana.azzeraTensore();
    }
    
    
}


