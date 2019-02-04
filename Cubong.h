/* 

-------------------------------------
_____________________________________
*/


/*

Pin dello Shift register SN74HC595N:

1 - Q1
2 - Q2
3 - Q3
4 - Q4
5 - Q5
6 - Q6
7 - Q7
8 - GND
9 - Serial Data output
Il serial data output (chiamato anche Q7') è nientemeno che la continuazione dello shiftregister:
ad ogni commutazione di clock (durante latch==0, cioé in acquisizione seriale), i bit vengono
shiftati ogni volta di una posizione; quando si raggiunge l'ultima posizione, i bit rimanenti 
vengono mandati sulla Q7' in attesa di essere presi da un altro shift register in cascata con
il medesimo clock e latch.

10 - Master Reclear (+5)
11 - Clock
12 - Latch
13 - Output Enable (GND)
14 - Serial Data input
15 - Q0
16 - Vcc

*/


#ifndef Cubong_h
#define Cubong_h

#include "Arduino.h"




class Cubong
{

public:

Cubong (int data, int latch, int clock, int enable, int l0, int l1, int l2, int l3, int l4);

void ciao();
void decoordinatore(int i, int j, int k, int *data);
void serialOut (int *data);
void led(int x, int y, int z);
void piano(int z);
void spengi();
void riempiCubo(void);

/* aggiornamento */
void sendBuffer2(int size);
int tensoreToBuffer2(int z);
int accendiCubo2(long int time);
void sendLayer(int z);


// Funzioni con buffer e tensore
void 	letteraM	(int x, int time);
void 	letteraI	(int x, int time);
void 	letteraS	(int x, int time);

int 	lampeggiaCubo	(int ritardo, int ripetizioni);
void 	spengiCubo	(void);
int  	accendiCubo	(long int time);
void 	fillPiano	(int z);

void 	getTensore	(bool source[][5][5]);

void	accendiPiano	(int z);
void 	sendBuffer	(void);
void 	testTensore	(void);

void 	printaBuffer	(void);
void 	printaTensore	(void);
void 	printaTensore_riga(void);
void 	printaTensore_piano(int z);
void 	printaTensore_elementi(void);

int 	tensoreToBuffer	(int z);
void 	azzeraBuffer	(void);
void 	stampaPiano	(int z);
void 	azzeraTensore	(void);
void 	add		(int x, int y, int z);


bool tensore[5][5][5];
	
private:

// buffer
int buffer[32];

int _clock;
int _latch;
int _data;
int _enable;

// Layer
int _l0;
int _l1;
int _l2;
int _l3;
int _l4;


int somma(int *data, int size);

};




/**/
class Led
{
public:
int x,y,z;
};



// Box diventa sempre piu vicina ad un oggetto in un film
class Box
{

public:



Box();

void 	azzeraTensore	(void);
void 	add		(int x, int y, int z);
void addCumulativo(int x, int y, int z);
void 	printaTensore_riga(void);
void 	film1	(void);

bool tensore[5][5][5];



void 	move	(int x, int y, int z);
int pos[3];

private:
int ledAcceso;

};


/**/

void 	sendBox	(Box input, Cubong* storage);

Box somma (Box addendo1, Box addendo2);

#endif
