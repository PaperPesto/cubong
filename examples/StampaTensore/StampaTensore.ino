//Riempi Cubo

/*
Dimostra l'utilizzo di Tensore[][][]
nella libreria
*/

#include <Cubong.h>

Cubong cuborana(7,6,5);

void setup()
{

Serial.begin(9600);
}

void loop()

{
  int i,j,k;
  
  for(i=0;i<5;i++){	for(j=0;j<5;j++){	for(k=0;k<5;k++){	
  cuborana.riempiTensore(i,j,k);
  cuborana.stampaTensore();
  }}}
  cuborana.azzeraTensore();
}


