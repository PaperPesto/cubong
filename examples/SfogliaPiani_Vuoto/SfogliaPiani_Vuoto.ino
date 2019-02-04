// Sfoglia Vuoto
// Sfoglia un piano spento

#include <Cubong.h>

Cubong cubicenbalo(7,6,5);

void setup()
{}

int k; 
int spento;
int ripeti=0;

void loop()
  {
 
  for(spento=0;spento<5;spento++)
    {
    
    while(ripeti<250)
      {  
      for(k=0;k<5;k++, ripeti++)  
         {
         if(k!=spento)  cubicenbalo.piano(k); 
         }
      }
    ripeti=0;
    }

  }
  

