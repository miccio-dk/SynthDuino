/*
  Play.h - libreria contenente le funzioni che implementano 'suona'
  Riccardo Miccini - 23/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#ifndef Play_H
#define Play_H

#include "Arduino.h"
#include "Midi.h"
#include "Synthesis.h"
#include "Pads.h"
#include "Settings.h"

void playMidi(Setting set, char *ton[]);
void playWave(Setting set, char *ton[]);
void playMidiDrum(Setting set, PadSetting *pset);

void loadNotes(byte *note, byte tonality, byte octave);

int noteToFreq(byte note);
void playNote(byte note);
void stopNote();

#endif
