# Cubong

Una libreria Arduino per controllare un cubo LED 5x5x5 utilizzando shift register.

## Panoramica

Cubong è una libreria progettata per semplificare il controllo di un cubo LED 5x5x5 (125 LED totali) utilizzando la piattaforma Arduino. La libreria usa shift register (SN74HC595N) per il multiplexing della matrice LED, permettendo di controllare tutti i 125 LED usando solo pochi pin digitali.

## Caratteristiche

- **Controllo LED Semplice**: Accendi/spegni singoli LED usando coordinate 3D (x, y, z)
- **Gestione Piani**: Controlla interi piani (layer) del cubo
- **Sistema Tensore 3D**: Usa un array booleano 3D per rappresentare lo stato dell'intero cubo
- **Supporto Animazioni**: Funzioni integrate per creare pattern e animazioni
- **Visualizzazione Testo**: Visualizza lettere (M, I, S) nel cubo
- **Classe Box**: Crea oggetti animati che possono muoversi attraverso il cubo
- **Esempi Multipli**: Include 10 sketch di esempio che dimostrano varie funzionalità

## Requisiti Hardware

- Scheda Arduino (Uno, Mega, o compatibile)
- Cubo LED 5x5x5
- 4x shift register SN74HC595N (o più, a seconda della configurazione)
- Array di transistor Darlington ULN2003 per il controllo dei piani
- Resistenze per i LED
- Alimentatore (sufficiente per tutti i LED)

### Piedinatura Shift Register (SN74HC595N)

La libreria è progettata per funzionare con lo shift register SN74HC595N. Configurazione pin:

```
1  - Q1 (Uscita 1)
2  - Q2 (Uscita 2)
3  - Q3 (Uscita 3)
4  - Q4 (Uscita 4)
5  - Q5 (Uscita 5)
6  - Q6 (Uscita 6)
7  - Q7 (Uscita 7)
8  - GND
9  - Q7' (Uscita Dati Seriale per cascata)
10 - Master Reset (collegare a +5V)
11 - Clock
12 - Latch
13 - Output Enable (collegare a GND o pin Arduino)
14 - Serial Data Input (Ingresso Dati Seriale)
15 - Q0 (Uscita 0)
16 - Vcc (+5V)
```

## Installazione

### Arduino IDE

1. Scarica questo repository come file ZIP
2. Nell'Arduino IDE, vai su **Sketch** → **Include Library** → **Add .ZIP Library...**
3. Seleziona il file ZIP scaricato
4. La libreria sarà installata e disponibile nei tuoi sketch

### Installazione Manuale

1. Scarica questo repository
2. Copia la cartella `Cubong` nella cartella delle librerie Arduino:
   - Windows: `Documenti\Arduino\libraries\`
   - Mac: `~/Documents/Arduino/libraries/`
   - Linux: `~/Arduino/libraries/`
3. Riavvia l'Arduino IDE

## Guida Rapida

### Esempio Base

```cpp
#include <Cubong.h>

// Crea oggetto Cubong
// Parametri: data, latch, clock, enable, layer0, layer1, layer2, layer3, layer4
Cubong cubo(7, 6, 5, 4, 8, 9, 10, 11, 12);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Accendi un singolo LED alla posizione (2, 2, 2)
  cubo.led(2, 2, 2);
  delay(1000);
  
  // Spegni tutti i LED
  cubo.spengi();
  delay(1000);
}
```

## Riferimento API

### Classe Cubong

#### Costruttore

```cpp
Cubong(int data, int latch, int clock, int enable, int l0, int l1, int l2, int l3, int l4)
```

Crea un oggetto Cubong con le connessioni pin specificate.

**Parametri:**
- `data` - Pin dati seriali per shift register
- `latch` - Pin latch per shift register
- `clock` - Pin clock per shift register
- `enable` - Pin output enable per shift register
- `l0`, `l1`, `l2`, `l3`, `l4` - Pin di controllo dei piani (0-4)

#### Metodi Principali

##### Controllo LED

- `void led(int x, int y, int z)` - Accende un singolo LED alle coordinate (x, y, z)
- `void piano(int z)` - Accende tutti i LED nel piano z
- `void spengi()` - Spegne tutti i LED
- `void spengiCubo()` - Spegne il cubo (pulisce il buffer)

##### Operazioni sul Tensore

La libreria usa un array booleano 3D (tensore) per rappresentare lo stato del cubo:

- `void add(int x, int y, int z)` - Aggiunge un LED al tensore nella posizione (x, y, z)
- `void azzeraTensore()` - Azzera il tensore (imposta tutto a 0)
- `void fillPiano(int z)` - Riempie un intero piano nel tensore
- `void getTensore(bool source[][5][5])` - Copia il tensore da un'altra sorgente

##### Funzioni di Visualizzazione

- `int accendiCubo(long int time)` - Visualizza il tensore per il tempo specificato (millisecondi)
- `int accendiCubo2(long int time)` - Metodo di visualizzazione alternativo con cambio piano
- `void sendLayer(int z)` - Invia un piano specifico al cubo
- `int lampeggiaCubo(int ritardo, int ripetizioni)` - Fa lampeggiare il cubo

##### Visualizzazione Testo

- `void letteraM(int x, int time)` - Visualizza la lettera "M" alla posizione x
- `void letteraI(int x, int time)` - Visualizza la lettera "I" alla posizione x
- `void letteraS(int x, int time)` - Visualizza la lettera "S" alla posizione x

##### Funzioni di Debug

- `void printaTensore()` - Stampa lo stato del tensore sulla Seriale
- `void printaTensore_piano(int z)` - Stampa un piano specifico sulla Seriale
- `void printaTensore_riga()` - Stampa il tensore in formato riga sulla Seriale
- `void printaBuffer()` - Stampa il contenuto del buffer sulla Seriale

### Classe Box

La classe Box permette di creare oggetti animati che possono muoversi attraverso il cubo.

#### Costruttore

```cpp
Box()
```

Crea un nuovo oggetto Box con il proprio tensore.

#### Metodi

- `void add(int x, int y, int z)` - Aggiunge un LED al tensore Box
- `void addCumulativo(int x, int y, int z)` - Aggiunge LED con effetto cumulativo
- `void azzeraTensore()` - Azzera il tensore Box
- `void move(int x, int y, int z)` - Muove il singolo LED del Box in una nuova posizione
- `void printaTensore_riga()` - Stampa il tensore Box sulla Seriale

#### Funzioni Helper

- `void sendBox(Box input, Cubong* storage)` - Trasferisce il tensore Box a Cubong
- `Box somma(Box addendo1, Box addendo2)` - Combina due oggetti Box (operazione OR)

## Esempi

La libreria include diversi sketch di esempio nella cartella `examples/`:

### LampeggiaCubo_Input
Dimostra il lampeggio del cubo con ritardo variabile controllato dall'ingresso analogico.

### Miss
Visualizza le lettere "MISS" sul cubo con posizionamento variabile.

### RiempiCubo
Riempie il cubo in modo casuale, un LED alla volta.

### SfogliaLed
Scansiona i singoli LED in sequenza.

### SfogliaPiani
Scorre attraverso tutti e cinque i piani del cubo.

### SfogliaPiani_Vuoto
Simile a SfogliaPiani ma inizia con piani vuoti.

### SfogliaPiani_input
Scorrimento piani con velocità variabile dall'ingresso analogico.

### StampaTensore
Dimostra il sistema tensore stampando pattern.

### StampaTensore_Piani
Mostra come costruire pattern piano per piano usando il tensore.

### TestTensore
Testa la funzionalità del tensore con vari pattern.

## Suggerimenti d'Uso

1. **Alimentazione**: Assicurati che il tuo alimentatore possa gestire tutti i LED. A piena luminosità, 125 LED possono assorbire corrente significativa.

2. **Frequenza di Aggiornamento**: La funzione `accendiCubo()` usa il multiplexing. Chiamala frequentemente con intervalli di tempo brevi per una visualizzazione fluida.

3. **Flusso di Lavoro Tensore**: Il flusso di lavoro tipico è:
   - Azzera tensore: `cubo.azzeraTensore()`
   - Aggiungi LED: `cubo.add(x, y, z)`
   - Visualizza: `cubo.accendiCubo(durata)`

4. **Oggetti Multipli**: Usa la classe Box per creare oggetti animati multipli che possono essere combinati.

## Dettagli Tecnici

### Multiplexing

La libreria usa il multiplexing a divisione di tempo per controllare il cubo:
- Solo un piano è attivo alla volta
- La libreria scorre rapidamente attraverso i piani (tipicamente 5ms per piano)
- La persistenza della visione crea l'illusione che tutti i LED siano accesi simultaneamente

### Sistema Buffer

Internamente, la libreria mantiene:
- Un buffer a 32 bit per l'uscita dello shift register
- Un tensore booleano 5x5x5 che rappresenta lo stato del cubo
- Conversione automatica dal formato tensore al formato buffer

## Contribuire

I contributi sono benvenuti! Sentiti libero di inviare pull request o aprire issue per bug e richieste di funzionalità.

## Licenza

Questo progetto è open source. Verifica con il proprietario del repository per i termini specifici della licenza.

## Crediti

Creato da PaperPesto

---

*Nota: Questa libreria è progettata per scopi educativi e progetti DIY di cubi LED. Per uso in produzione, potrebbe essere richiesta ottimizzazione aggiuntiva.*
