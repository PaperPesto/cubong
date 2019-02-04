// Prova di Box e Cubong per fare un filmino

#include <Cubong.h>

Cubong   cubo(7,6,5);
Box      goccia;
Box      suolo;
Box      totale;

int i,j,k;

int x0, y0;

int analogInput = A0;
int ritardo;

int reset;

int control[5][5];


void setup()

{

  Serial.begin(9600);
  // Inizializzazioni
  reset = 0;
  for(i=0;i<5;i++) for(j=0;j<5;j++) control[i][j]=0;
}


void loop()

{
    
  x0 = random(5);  
  y0 = random(5);
  
  if(control[x0][y0]<5)
  {
    
  control[x0][y0]++; 
  reset++;  // è entrato nella colonna
  
  // Caduta goccia
  for(k=0;k<5;k++)
    {  
    
    ritardo = (float)analogRead(analogInput)/1023*400; 
    
    // se quello sotto è pieno
    if(suolo.tensore[x0][y0][k+1])
      {
       
       suolo.add(x0,y0,k);
       break; 
        
      }
    
    goccia.move(x0,y0,k);
    sendBox(  somma(goccia,suolo)   ,&cubo);
    cubo.accendiCubo(ritardo);
    }
   
  suolo.add(x0,y0,4);  
    
  }
  
  else // se control == 5
    {
    
    }
    
   
   
   
   
   Serial.println(reset);
}
  

