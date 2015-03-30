/*
  Play.cpp - libreria contenente le funzioni che implementano 'suona'
  Riccardo Miccini - 23/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#include "Play.h"

// array contenenti gli intervalli in semitoni delle scale
byte major[] = {2, 2, 1, 2, 2, 2, 1};
byte minor[] = {2, 1, 2, 2, 1, 2, 2};
byte blues[] = {3, 2, 1, 1, 3, 2}; 

// playMidiDrum
// gestisce la modalità drum (batteria)
void playMidiDrum(Setting set, PadSetting *pset)
{
  boolean pads[8];
  boolean pads_old[8];
  byte i;
  
  // variabili relative al midi
  Serial.begin(31250);    //31250
  Midi midi;
  midi._canale = set.channel;
  midi.prgChange(set.patch);
  
  String str = "#  can. in uso: ";
  str = str + set.channel;
  if(set.channel < 10)
    str = str + "  #";
  else
    str = str + " #";
  
  showText("####################"
          ,"#    DRUM  MODE    #"
          ,str
          ,"####################");
  
  scanDigitalPads(pads_old, 7, 8, 9, 10);
  
  while(buttonCheck(A0) != BACK)
  {
    scanDigitalPads(pads, 7, 8, 9, 10);
    
    for(i=0; i<8; i++)
    {
      if(pads[i] > pads_old[i])
      {
        midi.noteON(pset[i].note, pset[i].velocity);
        /*Serial.print("pad n ");
        Serial.print(pset[i].note);
        Serial.println(" premuto!");*/
      }
      if(pads[i] < pads_old[i])
      {
        midi.noteOFF(pset[i].note);
        /*Serial.print("pad n ");
        Serial.print(pset[i].note);
        Serial.println(" rilasciato!");*/
      }
      pads_old[i] = pads[i];
    }
  }
}


// playMidi
// gestisce la modalità midi
void playMidi(Setting set, char *ton[])
{
  boolean pads[8];
  boolean pads_old[8];
  byte note[8];
  byte i;
  
  // inizializzo il vettore contenente le note
  // in base alla tonalità corrente
  loadNotes(note, set.tonality, set.octave);
  
  // variabili relative al midi
  Serial.begin(31250);    //31250
  Midi midi;
  midi._canale = set.channel;
  midi.prgChange(set.patch);
  
  String str1 = " can. in uso: ";
  str1 = str1 + set.channel;
  
  String str2 = " tonalita': ";
  str2 = str2 + ton[set.tonality] + " " + set.octave;
  
  showText("#### MIDI  MODE ####"
          ,str1
          ,str2
          ,"####################");
  
  scanDigitalPads(pads_old, 7, 8, 9, 10);
  
  while(buttonCheck(A0) != BACK)
  {
    scanDigitalPads(pads, 7, 8, 9, 10);
    
    for(i=0; i<8; i++)
    {
      if(pads[i] > pads_old[i])
      {
        midi.noteON(note[i], 120);
      }
      if(pads[i] < pads_old[i])
      {
        midi.noteOFF(note[i]);
      }
      pads_old[i] = pads[i];
    }
  }
}


// playWave
// gestisce la modalità piano
void playWave(Setting set, char *ton[])
{
  boolean pads[8];
  boolean pads_old[8];
  byte note[8];
  byte i;
  
  // inizializzo il vettore contenente le note
  // in base alla tonalità corrente
  loadNotes(note, set.tonality, set.octave);

  String str = "# ton.: ";
  str = str + ton[set.tonality] + " " + set.octave;
  
  showText("####################"
          ,"#    PIANO MODE    #"
          ,str
          ,"####################");
  
  scanDigitalPads(pads_old, 7, 8, 9, 10);
  
  while(buttonCheck(A0) != BACK)
  {
    scanDigitalPads(pads, 7, 8, 9, 10);
    
    for(i=0; i<8; i++)
    {
      if(pads[i] > pads_old[i])
      {
        playNote(note[i]);
      }
      if(pads[i] < pads_old[i])
      {
        stopNote();
      }
      pads_old[i] = pads[i];
    }
  }
}



// loadNotes
// carica il vettore contenente i valori midi delle note
void loadNotes(byte *note, byte tonality, byte octave)
{
  byte i;
  
  switch(tonality)
  {
    case FREE:  for(i=0; i<8; i++)
                  note[i] = 24 + 12*(octave-1) + i;
                break;
    
    case CM:    note[0] = 24 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + major[i-1];
                break;
    
    case GM:    note[0] = 31 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + major[i-1];
                break;
    
    case DM:    note[0] = 26 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + major[i-1];
                break;
    
    case AM:    note[0] = 33 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + major[i-1];
                break;
    
    case Am:    note[0] = 33 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + minor[i-1];
                break;
    
    case Dm:    note[0] = 26 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + minor[i-1];
                break;
    
    case Gm:    note[0] = 31 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + minor[i-1];
                break;
    
    case Cm:    note[0] = 24 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + minor[i-1];
                break;
    
    case Gpm:    note[0] = 31 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + blues[(i-1)%6];
                break;
    
    case Epm:    note[0] = 28 + 12*(octave-1);
                for(i=1; i<8; i++)
                  note[i] = note[i-1] + blues[(i-1)%6];
                break;
  }
}

// noteToFreq
// converte il numero midi della nota in un valore di frequenza
int noteToFreq(byte note)
{
  double freq = 440.0 * pow(2.0, (double)(note - 69)/12);
  return (int)freq;
}

// playNote
// riproduce una nota
void playNote(byte note)
{
  tone(6, noteToFreq(note));
}

// stopNote
// interrompe l'audio
void stopNote()
{
  noTone(6);
}
