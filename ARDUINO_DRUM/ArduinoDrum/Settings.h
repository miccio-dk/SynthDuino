/*
  Settings.h - Libreria per la gestione delle impostazioni della batteria
  Riccardo Miccini - 17/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#ifndef Settings_H
#define Settings_H

#include "Arduino.h"
#include "MenuLCD.h"

// identificatori delle tonalità
#define FREE 0
#define CM   1
#define GM   2
#define DM   3
#define AM   4
#define Am   5
#define Dm   6
#define Gm   7
#define Cm   8
#define Gpm  9
#define Epm  10

// identificatori del sottomenu pad
#define NOTE  5
#define VELO  10

// impostazioni pad
typedef struct
{
  byte note;      // nota midi assegnata al pad
  byte velocity;  // velocity di default del pad
} PadSetting;

// impostazioni varie
typedef struct
{
  byte channel;
  byte octave;
  byte sens;
  byte patch;
  byte waveform;
  byte threshold;
  byte tonality;
} Setting;

void editSettingT(String title, String descr, byte *val, char *list[]);
void editSettingN(String title, String descr, byte *val, byte min, byte max);

byte chosePad();
void editPadSettings(PadSetting *set, byte n_pad);

#endif
