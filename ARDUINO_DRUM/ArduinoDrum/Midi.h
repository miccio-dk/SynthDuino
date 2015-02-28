/*
  Midi.h - Libreria per l'accesso alle funzioni MIDI di base
  Riccardo Miccini - 19/02/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#ifndef Midi_h
#define Midi_h

#include "Arduino.h"

// midi drumset
#define KICK1  35
#define KICK2  36
#define SNARE1 38
#define SNARE2 40
#define HH_CL  42
#define HH_OP  46
#define HH_FT  44
#define TOM1   43
#define TOM2   45
#define TOM3   47
#define CRASH  49
#define RIDE   51
#define CHINA  42
#define SPLASH 55
#define STICKS 31

class Midi
{
  public:
    Midi(byte led, byte canale);
    Midi(byte canale);
    Midi();
    byte _canale;
    
    void noteON(byte nota, byte forza);
    void noteOFF(byte nota);
    void prgChange(byte banco);
    
  private:
    byte _led;
    
    void midiMSG(byte stato, byte valore1);
    void midiMSG(byte stato, byte valore1, byte valore2);  
};

#endif
