/*
  Synthesis.h - Libreria per la sintesi di suoni e forme d'onda
  Riccardo Miccini, Davide Montini - 18/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
    
  Alcune parti di codice sono state prese dal progetto "Arduino 
  Theremin/Synth", sviluppato da Max Pierson e rilasciato sotto 
  licenza WTFPL.
*/

#ifndef Synthesis_H
#define Synthesis_H

#include "Arduino.h"


// identificatori delle forme d'onda (timbri)
#define SINE   0
#define SQUARE 1
#define RECT   2
#define TRIANG 3
#define SAW    4

// identificatori vari
#define SAMPLE_LEN 32    // lunghezza dell'array
#define SAMPLE_MAX 255   // valore massimo

// creazione di forme d'onda
void loadWave(byte * vet, byte wave);
void createSin(byte *vet);
void createSquare(byte *vet);
void createTriang(byte *vet);
void createSaw(byte *vet);
void createRect(byte *vet, byte dc);

// inizializzazione
void initSynth();



#endif
