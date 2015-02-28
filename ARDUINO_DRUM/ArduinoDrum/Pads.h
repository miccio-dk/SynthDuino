/*
  Pads.h - Libreria per la gestione dei pad della batteria
  Riccardo Miccini - 18/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#ifndef Pads_H
#define Pads_H

#include "Arduino.h"

void scanPads(byte *vet, byte analog_pin, byte pin_a, byte pin_b, byte pin_c);

#endif
