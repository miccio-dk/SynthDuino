/*
  Play.h - libreria contenente le funzioni che implementano 'suona'
  Riccardo Miccini - 23/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#ifndef Pads_H
#define Pads_H

#include "Arduino.h"
#include "Midi.h"
#include "Synthesis.h"
#include "Pads.h"

void playMidi(Setting set);
void playWave(Setting set);
void playMidiDrum(Setting set, PadSetting pset);

#endif
