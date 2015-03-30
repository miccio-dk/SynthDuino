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
  Serial.begin(9600);    //31250
  pinMode(led, OUTPUT);
  _led = led;
  _canale = canale;
}
Midi::Midi(byte canale)
{
  _canale = canale;
}
Midi::Midi()
{
  _canale = 0;
}

// noteON
// invia un messaggio di inizio dell'evento sonoro 
void Midi::noteON(byte nota, byte forza)
{
  midiMSG(0x90|((_canale-1)&0x0F), nota, forza);
}

// noteOFF
// invia un messaggio di fine dell'evento sonoro
void Midi::noteOFF(byte nota)
{
  midiMSG(0x80|((_canale-1)&0x0F), nota, 0x00);
}

// prgChange
// invia un messaggio per il cambio del banco suoni
void Midi::prgChange(byte banco)
{
  midiMSG(0xC0|((_canale-1)&0x0F), banco);
}

// midiMSG
// invia un messaggio MIDI generico (1 value byte)
void Midi::midiMSG(byte stato, byte valore)
{
  valore &= 0x7F;
  //digitalWrite(_led, HIGH);      //indica l'invio della trasmissione
  Serial.write(stato);           //invia il byte di stato
  Serial.write(valore);          //invia il value byte 
  //digitalWrite(_led, LOW);       //indica la fine della trasmissione
}

// midiMSG
// invia un messaggio MIDI generico (2 value bytes)
void Midi::midiMSG(byte stato, byte valore1, byte valore2)
{
  valore1 &= 0x7F;
  valore2 &= 0x7F;
  //digitalWrite(_led, HIGH);      //indica l'invio della trasmissione
  Serial.write(stato);           //invia il byte di stato
  Serial.write(valore1);         //invia il primo value byte 
  Serial.write(valore2);         //invia il secondo value byte
  //digitalWrite(_led, LOW);       //indica la fine della trasmissione
}

