/*
  Pads.cpp - Libreria per la gestione dei pad della batteria
  Riccardo Miccini - 18/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#include "Pads.h"


// scanPads
// gestisce il multiplexer al quale sono connessi i pad
void scanPads(byte *vet, byte analog_pin, byte pin_a, byte pin_b, byte pin_c)
{
  int i;
  
  for (i=0; i<8; i++)
  {
    digitalWrite(pin_a, bitRead(i,0));
    digitalWrite(pin_b, bitRead(i,1));
    digitalWrite(pin_c, bitRead(i,2));
    
    vet[i] = analogRead(analog_pin);
  }
}
