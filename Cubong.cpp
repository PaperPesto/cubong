/* 

Cubong :: Libreria
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







#include "Arduino.h"
#include "Cubong.h"







// Costruttore.
Cubong::Cubong(int data, int latch, int clock, int enable, 
		int l0, int l1, int l2, int l3, int l4)
{

pinMode(clock, OUTPUT);
pinMode(latch, OUTPUT);
pinMode(data, OUTPUT);
pinMode(enable, OUTPUT);

pinMode(l0, OUTPUT);
pinMode(l1, OUTPUT);
pinMode(l2, OUTPUT);
pinMode(l3, OUTPUT);
pinMode(l4, OUTPUT);


_clock = clock;
_latch = latch;
_data = data;
_enable = enable;

_l0=l0;
_l1=l1;
_l2=l2;
_l3=l3;
_l4=l4;


azzeraTensore();
azzeraBuffer();

}












/*
	FUNZIONI PRINT
*/

void Cubong::printaTensore(void)
{

int i;

Serial.println("Printa Tensore");

for(i=0;i<5;i++)	{printaTensore_piano(i);	Serial.println();}
}


void Cubong::printaTensore_piano(int z)
{

Serial.print("Piano: ");	Serial.println(z);		
Serial.println("-------------");

int i,j;

for(i=0;i<5;i++)
	{
	for(j=0;j<5;j++)
		{
		Serial.print(tensore[i][j][z]);
		Serial.print(" ");
		}
	Serial.println();
	}
}




void Cubong::printaTensore_riga(void)
{

int i,j,k;

Serial.println("Printa Tensore");

Serial.print("Piano");		Serial.print('\t'); 
Serial.print("Riga");		Serial.print('\t'); 
Serial.print("Colonna");	Serial.print('\t'); 
Serial.print("Valore");
Serial.println();
Serial.println("-----------------------");

for(k=0;k<5;k++)
	{
	for(i=0;i<5;i++)
		{
		for(j=0;j<5;j++)
			{
			Serial.print(k); Serial.print('\t'); 
			Serial.print(i); Serial.print('\t'); 
			Serial.print(j); Serial.print('\t');
			Serial.println(tensore[i][j][k]);
			}
		}
	}
}


void Cubong::printaTensore_elementi(void)
{
int i,j,k;

for(i=0;i<5;i++){
for(j=0;j<5;j++){
for(k=0;k<5;k++){


Serial.print(i);Serial.print(j);Serial.print(k); Serial.print('\t');
Serial.println( *(*(*(tensore+i)+j)+k) );	// IMPORTANTE

}}}
}



void Cubong::printaBuffer()
{

Serial.println("Printa Buffer:");

int i;


for(i=0;i<5;i++)
	{
	Serial.print(i); Serial.print(" "); Serial.println(buffer[i]);
	}
Serial.println("--");

for(i=5;i<10;i++)
	{
	Serial.print(i); Serial.print(" "); Serial.println(buffer[i]);
	}
Serial.println("--");

for(i=10;i<15;i++)
	{
	Serial.print(i); Serial.print(" "); Serial.println(buffer[i]);
	}
Serial.println("--");

for(i=15;i<20;i++)
	{
	Serial.print(i); Serial.print(" "); Serial.println(buffer[i]);
	}
Serial.println("--");

for(i=25;i<30;i++)
	{
	Serial.print(i); Serial.print(" "); Serial.println(buffer[i]);
	}
Serial.println("--");

for(i=30;i<32;i++)
	{
	Serial.print(i); Serial.print(" "); Serial.println(buffer[i]);
	}
}







void Cubong::testTensore(void)
{

int i;

for(i=0;i<5;i++)
	{

	add(0,0,0);
	add(3,0,1);
	add(1,3,2);
	add(4,0,3);
	add(0,2,4);
	add(1,0,4);

	printaTensore();

	tensoreToBuffer(i);

	printaBuffer();

	sendBuffer();

	delay(5000);
	}
}



/*
Tensore e buffer devono essere sincronizzati il piu possibilie
*/


// Tensore -> Buffer
int Cubong::tensoreToBuffer (int z)
{

// Controllo. Restituisce -1 se ho sbagliato piano
if (z>=5)	return -1;


azzeraBuffer();


buffer[z]=1;

int i,j;
for(i=0;i<5;i++)
	{
	for(j=0;j<5;j++)
		{
		buffer[5+j+i*5] = tensore[i][j][z];
		}
	}

return 0;
}



// Tensore -> Buffer
int Cubong::tensoreToBuffer2 (int z)
{

// Controllo. Restituisce -1 se ho sbagliato piano
if (z>=5)	return -1;


azzeraBuffer();


int i,j;
for(i=0;i<5;i++)
	{
	for(j=0;j<5;j++)
		{
		buffer[j+i*5] = tensore[i][j][z];
		}
	}

return 0;
}





// Tensore -> (0,0,....,0)
void Cubong::azzeraTensore(void)
{
// inizializzo tensore a 0
int i,j,k;
for(i=0;i<5;i++)	for(j=0;j<5;j++)	for(k=0;k<5;k++)	tensore[i][j][k] = 0;

azzeraBuffer();
}




// Aggiunge un pixel al tensore
// (x,y,z) -> Tensore
void Cubong::add(int x, int y, int z)
{

tensore[x][y][z] = 1;
}



void Cubong::fillPiano(int z)
{

int i,j;

for(i=0;i<5;i++) for(j=0;j<5;j++) add(i,j,z);

}


// Il passaggio di multiarray segue questa definizione:
// ( array[][14][14]  )
// Box.tensore -> Cubong.tensore
void Cubong::getTensore(bool source[][5][5])
{
int i,j,k;
for(i=0;i<5;i++) {
for(j=0;j<5;j++) {
for(k=0;k<5;k++) {

//tensore[i][j][k] = *(*(*(source+i)+j)+k);	// Con i puntatori
tensore[i][j][k] = source[i][j][k];
//Serial.println(tensore[i][j][k]);
//Serial.println(source[i][j][k]);

}}} 
}





// Piano -> Buffer -> Cubo
void Cubong::accendiPiano(int z)
{

tensoreToBuffer(z);		// piano -> buffer
sendBuffer();			// buffer -> cubo
}




// Spedisce il buffer al cubo
void Cubong::sendBuffer(void)
{

int i;

// Inizio scrittura seriale
digitalWrite(_enable, HIGH);	// Disabilita gli output dello SR
digitalWrite(_latch, LOW);
for (i=31; i>=0; i--)
	{	
	digitalWrite(_clock, LOW);	
	digitalWrite(_data, buffer[i]);	
	digitalWrite(_clock, HIGH);
	}
digitalWrite(_latch, HIGH);
digitalWrite(_enable, LOW);	// Abilita gli output dello SR
//Fine scrittura seriale

//printaBuffer(); // AUX
}


// Spedisce il buffer2 al cubo
void Cubong::sendBuffer2(int size)
{

int i;

// Inizio scrittura seriale
digitalWrite(_enable, HIGH);	// Disabilita gli output dello SR
digitalWrite(_latch, LOW);
for (i=size-1; i>=0; i--)
	{	
	digitalWrite(_clock, LOW);	
	digitalWrite(_data, buffer[i]);	
	digitalWrite(_clock, HIGH);
	}
digitalWrite(_latch, HIGH);
digitalWrite(_enable, LOW);	// Abilita gli output dello SR
//Fine scrittura seriale

//printaBuffer(); // AUX
}




// Buffer -> (0,0,....,0)
void Cubong::azzeraBuffer (void)
{

int i;

// Azzero il Buffer --------------------------------
for(i=0;i<5;i++)			buffer[i]=0;
for(i=5;i<5+5*5;i++)			buffer[i]=0;

buffer[30] = 0;
buffer[31] = 0;
// -------------------------------------------------
}


// Spenge il cubo per time millisecondi
// Non annulla tensore, spenge solo il cubo
void Cubong::spengiCubo()
{

azzeraBuffer();
sendBuffer();
}



/*
Credo che gli ULN2003 non siano abbastanza veloci a commutare in termini di millisecondi. Infatti mi rimane un piano acceso quando gli accendo/spengo tutti
molto velocemente.
Spesso no nsi percepisce perché si accendono poco i led che precedenti
al piano acceso, proprio perché gli ULN non riescono a commutare (credo).
Lo stampaggio del tensore non è molto efficiente se devo stampare pochi
pixel alla volta, meglio usare altre funzioni.
*/


// CORE BUSINESS
// ritorna il tempo di esecuzione di un ciclo in millisecondi
int Cubong::accendiCubo(long int time)
// time indica il numero di millisecondi di esecuzione da fare
// Sembra che il tempo medio di esecuzione di un intero tensore sia 3 ms
// long int perché int da solo è un numero a 12 bit (4096 max)
{

int start, stop;
int i;

start = millis();

do
	{
	for(i=0;i<5;i++)
		{
		tensoreToBuffer(i);
		sendBuffer();
		//delay(5);
		}
	stop = millis();

	}
while(stop-start <= time);

//spengiCubo();	// Importante per spengere

return stop - start;
}



int Cubong::accendiCubo2(long int time)
{


int start, stop;
int i;

start = millis();

do
	{
	for(i=0;i<5;i++)
		{
		sendLayer(i);
		delay(1);
		}
	stop = millis();

	}
while(stop-start <= time);

//spengiCubo();	// Importante per spengere

return stop - start;
}


// Aggiornamento
void Cubong::sendLayer(int z)
{

// Spengo i piani
digitalWrite(_l0, LOW);
digitalWrite(_l1, LOW);
digitalWrite(_l2, LOW);
digitalWrite(_l3, LOW);
digitalWrite(_l4, LOW);

// Accendo il piano scelto
if(z==0)	digitalWrite(_l0, HIGH);
if(z==1)	digitalWrite(_l1, HIGH);
if(z==2)	digitalWrite(_l2, HIGH);
if(z==3)	digitalWrite(_l3, HIGH);
if(z==4)	digitalWrite(_l4, HIGH);

// Mando la matrice del piano
tensoreToBuffer2(z);
sendBuffer2(25);
}



int Cubong::lampeggiaCubo(int ritardo, int ripetizioni)
{
int start, stop;
start = millis();

int i;
for(i=0;i<ripetizioni;i++)
	{
	accendiCubo(ritardo);
	spengiCubo();
	delay(ritardo);
	}

stop = millis();

return stop - start;
}



void Cubong::letteraM(int x, int time)
{

azzeraTensore();

add(x,0,4);
add(x,2,4);
add(x,4,4);

add(x,0,3);
add(x,2,3);
add(x,4,3);

add(x,0,2);
add(x,2,2);
add(x,4,2);

add(x,0,1);
add(x,1,1);
add(x,4,1);
add(x,3,1);

add(x,0,0);
add(x,4,0);


accendiCubo(time);
sendBuffer();
}

void Cubong::letteraI(int x, int time)
{

azzeraTensore();

add(x,0,4);
add(x,1,4);
add(x,2,4);
add(x,3,4);
add(x,4,4);

add(x,2,3);


add(x,2,2);


add(x,2,1);


add(x,0,0);
add(x,1,0);
add(x,2,0);
add(x,3,0);
add(x,4,0);



accendiCubo(time);
sendBuffer();
}



void Cubong::letteraS(int x, int time)
{

azzeraTensore();

add(x,4,4);
add(x,1,4);
add(x,2,4);
add(x,3,4);


add(x,0,3);


add(x,1,2);
add(x,2,2);
add(x,3,2);


add(x,4,1);


add(x,0,0);
add(x,3,0);
add(x,2,0);
add(x,1,0);




accendiCubo(time);
sendBuffer();
}



/*

Mettere una funzione di inizializzazione e benvenuto con le lettere

*/

/* :::::::::::::::::::::::::::: BOX ::::::::::::::::::::::::::::: */

// Costruttore di Box
Box::Box (void)
{
azzeraTensore();

ledAcceso = 0;	// Significa nessun led acceso
pos[0]=0;
pos[1]=0;
pos[2]=0;
}


// Tensore -> (0,0,....,0)
void Box::azzeraTensore(void)
{
int i,j,k;
for(i=0;i<5;i++)	for(j=0;j<5;j++)	for(k=0;k<5;k++)	tensore[i][j][k] = 0;
}


// (x,y,z) -> Tensore
void Box::add(int x, int y, int z)
{
tensore[x][y][z] = 1;
}



// (x,y,z) -> Tensore cumulativo
void Box::addCumulativo(int x, int y, int z)
{
if (tensore[x][y][z])	tensore[x][y][z-1] = 1;
else			tensore[x][y][z] = 1;
}


void Box::printaTensore_riga(void)
{

int i,j,k;

Serial.println("Printa Tensore");

Serial.print("Piano");		Serial.print('\t'); 
Serial.print("Riga");		Serial.print('\t'); 
Serial.print("Colonna");	Serial.print('\t'); 
Serial.print("Valore");
Serial.println();
Serial.println("-----------------------");

for(k=0;k<5;k++)
	{
	for(i=0;i<5;i++)
		{
		for(j=0;j<5;j++)
			{
			Serial.print(k); Serial.print('\t'); 
			Serial.print(i); Serial.print('\t'); 
			Serial.print(j); Serial.print('\t');
			Serial.println(tensore[i][j][k]);
			}
		}
	}
}



// Funzione che prende due classi in ingresso
// storage viene preso con il puntatore cosi da modificarla veramente
// Sempre per dare maggior risalto al fatto che Cubong è assoluta
// Mentre le Box possono essere tante
// ES: sendBox(scatola, &cubetto);
// Box -> Cubong.tensore -> Buffer -> Cubo
// Questa funzione in pratica aggiorna il tensore di Cubong
void sendBox(Box input, Cubong* storage)
{

storage->getTensore( input.tensore );
}


// Funzione che modifica il tensore di Box in base al t passato
// t rappresenta il tempo del "film" e box pogni volta ne modifica il fotogramma
void Box::film1()
{


}



// Quando chiamo moveLed, si azzerano tutti i led di Box tranne quello di led
void Box::move(int x, int y, int z)
{

// spengo il led precedente se acceso
if(ledAcceso)	tensore[pos[0]][pos[1]][pos[2]]=0;

// Aggiorno la posizione del nuovo led acceso
pos[0]=x;
pos[1]=y;
pos[2]=z;
ledAcceso = 1;

// accendo effettivamente il led
tensore[x][y][z]=1;
}



/*
Adesso la parte importante, per fare dei film, è creare più oggetti Box
per farli interagire fra di loro, ad esempio sommandoli insieme o facendone 
la differenza tra i tensori. Ciè che mi serve dunque è una funzione 
che sommi due Box insieme e restituisca una Box in unscita che abbia la somma
dei tensori. Questo l'ho visto perché è comodo un oggetto goccia e uno ambiente
goccia si modifica in continuazione e scende, mentre ambiente si modifica solo
alla fine dell'esecuzione di goccia. Ciò che devo stampare è
ambiente = goccia + suolo
*/

Box somma (Box addendo1, Box addendo2)
{
int i,j,k;

Box risultato;

for(i=0;i<5;i++){
for(j=0;j<5;j++){
for(k=0;k<5;k++){
risultato.tensore[i][j][k] = addendo1.tensore[i][j][k] || addendo2.tensore[i][j][k];
}}}

return risultato;

}






















//Stamperà il tensore al piano z
void Cubong::stampaPiano(int z)

{

const int righe = 5;
const int colonne = 5;
const int altezza = 5;

int i,j,k;

int t;


buffer[z]=1;	// Accende il piano z

for(i=0;i<5;i++)
	{	
	for(j=0;j<5;j++)
		{
		if(tensore[i][j][z])	buffer[5 + j + i*5]=1;	
		}
	}

serialOut(buffer);
}




// Stampa di prova.
void Cubong::ciao()
{

Serial.println("ciao");
}



// Sputa in uscita un vettore <data> di lunghezza <lenght>.
// Lo sputa fuori ribaltandolo, perché lo shift register prende i valori
// all'incontrario rispetto all'ordine vettoriale e quello delle uscite Q1. Q2, ecc
// dello shift register.
/*

Posizioni
Shiftreg.      Vettore
 4 3 2 1       1 2 3 4
_______________________
|- - - -| <-- |1 0 1 1|
|1 - - -| <-- |0 1 1 -|
|1 0 - -| <-- |1 1 - -|
|1 0 1 -| <-- |1 - - -|
|1 0 1 1| <-- |- - - -|

*/

void Cubong::serialOut (int *data)
{

int i;

// Inizio scrittura seriale
digitalWrite(_latch, 0);

for (i=32-1; i>=0; i--)
	{
	
	digitalWrite(_clock, 0);	
	
	digitalWrite(_data, data[i]);	

	digitalWrite(_clock, 1);
	}

// Fine scrittura seriale
digitalWrite(_latch, 1);
}




/* Riempie un vettore con la codifica multiplexing */
void Cubong::decoordinatore(int i, int j, int k, int *data)
{

const int righe = 5;
const int colonne = 5;
const int piani = 5;

int t;

// Core Business ---------------------------------
for(t=0;t<piani;t++)			data[t]=0;
for(t=piani;t<piani+righe*colonne;t++)	data[t]=0;

data[30] = 0;
data[31] = 0;

data[k]=1;
data[piani + j + i*colonne]=1;
// -------------------------------------------------
}



// Accende un singolo led
void Cubong::led(int x, int y, int z)
{

int data[32];

decoordinatore(x,y,z,data);

serialOut(data);
}




// Accende tutto un piano
void Cubong::piano(int z)
{


const int righe = 5;
const int colonne = 5;
const int piani = 5;

int t;
int data[32];

// Core Business ---------------------------------
for(t=0;t<piani;t++)			data[t]=0;
for(t=piani;t<piani+righe*colonne;t++)	data[t]=1;	// Tutti accesi

data[30] = 0;
data[31] = 0;

data[z]=1;
// -------------------------------------------------

serialOut(data);
}



// Spenge tutti i led
void Cubong::spengi()
{

const int righe = 5;
const int colonne = 5;
const int piani = 5;

int t;
int data[32];

for(t=0;t<piani;t++)			data[t]=0;
for(t=piani;t<piani+righe*colonne;t++)	data[t]=0;

data[30] = 0;
data[31] = 0;


serialOut(data);
}


void Cubong::riempiCubo(void)
{

int x,y,z;
int riga, colonna;



riga	=	random(5);
colonna	=	random(5);

int i;
for(z=0;z<5;z++)
	{
	
	led(riga, colonna, z);
	delay(15);
	}




}


// Fa la somma di un vettore
int Cubong::somma(int *data, int size)
{

int totale;
totale=0;

int i;
for(i=0;i<size;i++)	totale = totale + *(data+i);

return totale;
}






