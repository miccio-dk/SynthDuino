/*
  Midi.cpp - Libreria per l'accesso alle funzioni MIDI di base
  Riccardo Miccini - 19/02/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#include "Midi.h"

// Midi
// costruttori della classe Midi
Midi::Midi(byte led, byte canale)
{
  Serial.begin(31250);
  pinMode(led, OUTPUT);
  _led = led;
  _canale = canale;
}
Midi::Midi(byte canale)
{
  Serial.begin(31250);
  _canale = canale;
}
Midi::Midi()
{
  Serial.begin(31250);
  _canale = 0;
}

// noteON
// invia un messaggio di inizio dell'evento sonoro 
void Midi::noteON(byte nota, byte forza)
{
  midiMSG((0x90 | _canale), nota, forza);
}

// noteOFF
// invia un messaggio di fine dell'evento sonoro
void Midi::noteOFF(byte nota)
{
  midiMSG((0x80 | _canale), nota, 0x00);
}

// prgChange
// invia un messaggio per il cambio del banco suoni
void Midi::prgChange(byte banco)
{
  midiMSG((0x12 | _canale), banco);
}

// midiMSG
// invia un messaggio MIDI generico (1 value byte)
void Midi::midiMSG(byte stato, byte valore)
{
  digitalWrite(_led, HIGH);      //indica l'invio della trasmissione
  Serial.print(stato);           //invia il byte di stato
  Serial.print(valore);          //invia il value byte 
  digitalWrite(_led, LOW);       //indica la fine della trasmissione
}

// midiMSG
// invia un messaggio MIDI generico (2 value bytes)
void Midi::midiMSG(byte stato, byte valore1, byte valore2)
{
  digitalWrite(_led, HIGH);      //indica l'invio della trasmissione
  Serial.print(stato);           //invia il byte di stato
  Serial.print(valore1);         //invia il primo value byte 
  Serial.print(valore2);         //invia il secondo value byte
  digitalWrite(_led, LOW);       //indica la fine della trasmissione
}

