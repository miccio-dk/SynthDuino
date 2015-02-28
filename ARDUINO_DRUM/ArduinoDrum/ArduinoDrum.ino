/*
  Menu - Libreria per la gestione del display e del menù
  Riccardo Miccini - 19/02/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
  
  TO DO:
  - aggiungere le azioni da svolgere nei singoli menù
  - gestione delle impostazioni dei pads
  - suona?!?
  - algoritmi per far suonare le note nelle tonalità
  - trasferire il database del menu su eeprom
  
  DONE:
  - 19/02 scritta tutta la gestione del menù
  - 20/02 correzione dei bugs
  - 21/02 modifica impostazioni non funzionante
  - 26/02 modifica impostazioni completamente funzionante
  - 02/03 modifica impostazioni con selezione da array di valori
  - 03/03 inizio della conversione in libreria
  - 17/03 sistemato tutto in classi con funzioni etc
  - 18/03 creata libreria settings, synthesis e pads
  - 19/03 aggiunta la gestione del multiplexer
  - 23/03 aggiunto algoritmo per la creazione di forme d'onda
*/

#include <LiquidCrystal.h>
#include "Midi.h"
#include "MenuLCD.h"
#include "Settings.h"
#include "Synthesis.h"
#include "Play.h"

// database contenente le voci del menù
MenuItem menu[] = {
  {0, 255, "arduino drum v0.2"},
    {1, 0, "modalita' drum"},
      {4, 1, "impostazioni"},
        {12, 4, "forza si/no"},
        {13, 4, "canale midi"},
        {14, 4, "soglia"},
      {5, 1, "impostazioni pad"},
      {6, 1, "suona"},
    {2, 0, "modalita' piano"},
      {7, 2, "impostazioni"},
        {15, 7, "ottava"},
        {16, 7, "tonalita'"},
        {17, 7, "timbro"},
      {8, 2, "suona"},
    {3, 0, "modalita' midi"},
      {9, 3, "impostazioni"},
        {18, 9, "ottava"},
        {19, 9, "tonalita'"},
      {10, 3, "impostazioni midi"},
        {20, 10, "canale midi"},
        {21, 10, "banco suoni"},
      {11, 3, "suona"}
};

// tabelle varie di visualizzazione su setting
char *lst_sens[] = {"  NO", "  SI", NULL};
char *lst_waveform[] = {" SINE", "SQUARE", " RECT", "TRIANG", " SAW", NULL};
char *lst_tonality[] = {"FREE", "C Maj", "G Maj", "D Maj", "A Maj", "A min", "D min", "G min", "C min", "G blue", "E blue", NULL};

// preset delle varie impostazioni
Setting default_set = {1, 3, false, 1, 4, 180, 1};
PadSetting pads[8];

// variabili relative al midi
Midi midi(default_set.channel);

// variabili relative alla sintesi sonora
byte wave[SAMPLE_LEN];
volatile byte waveindex = 0;   //indice di posizionamento nell'array wave[]
int period = 3822;             //periodo della forma d'onda

void setup()
{
  // legge il numero di voci del menu
  setMenu_lenght(sizeof(menu)/20);
  
  //inizializza le funzioni del firmware
  initSynth();
  initDisplay();
  
  Serial.begin(9600);
  
  // carica impostazioni di default
  loadWave(wave, default_set.waveform);
  midi._canale = default_set.channel;
  midi.prgChange(default_set.patch);
    
  showIntro();
}

void loop()
{
  // aggiorna il display se il menu o la voce attiva sono cambiati
  if(cmpCurrent_menu() || cmpCurrent_sel() || cmpSthToDo())
  {
    menuPrint(getCurrent_menu(), getCurrent_sel(), menu);
    updateAll();
  }
  
  // controlla lo stato della pulsantiera e, in base al bottone
  // premuto, esegue determinate azioni
  switch(buttonCheck(A0))
  {
    case UP:   if(getCurrent_sel()-1 < getFirstOption(getCurrent_menu(), menu))
                 setCurrent_sel(getLastOption(getCurrent_menu(), menu));
               else
                 setCurrent_sel(getCurrent_sel()-1);
               break;
               
    case DOWN: if(getCurrent_sel()+1 > getLastOption(getCurrent_menu(), menu))
                 setCurrent_sel(getFirstOption(getCurrent_menu(), menu));
               else
                 setCurrent_sel(getCurrent_sel()+1);
               break;
               
    case SEL:  setCurrent_menu(getCurrent_sel());
               setCurrent_sel(getFirstOption(getCurrent_menu(), menu));
               if(getCurrent_menu() == getCurrent_sel())
                 setSthToDo(true);
               break;
               
    case BACK: if(getPreviousMenu(getCurrent_menu(), menu) != 255)
                 setCurrent_menu(getPreviousMenu(getCurrent_menu(), menu));
               setCurrent_sel(getFirstOption(getCurrent_menu(), menu));
               break;
  }
  
  if(getSthToDo())
  {
    doSomething(getCurrent_sel());
    updateAll();
    setSthToDo(false);
    setCurrent_menu(getPreviousMenu(getCurrent_menu(), menu));
    setCurrent_sel(getFirstOption(getCurrent_menu(), menu));
  }
}



// doSomething
// funzione che raccoglie tutte le possibili azioni ed esegue
// quella corrispondente alla variabile action
void doSomething(byte action)
{
  switch(action)
  {
    case 5:  break;
    case 6:  break;
    case 8:  break;
    case 11: break;
    case 12: editSettingT(getMenuTitle(getCurrent_menu(), menu), "attiva sensibilita'", &default_set.sens, lst_sens);
             break;
    case 13: editSettingN(getMenuTitle(getCurrent_menu(), menu), "canale midi in uso", &default_set.channel, 1, 16);
             midi._canale = default_set.channel-1;
             break;
    case 14: editSettingN(getMenuTitle(getCurrent_menu(), menu), "sensibilita' minima", &default_set.threshold, 0, 250);
             break;
    case 15: editSettingN(getMenuTitle(getCurrent_menu(), menu), "ottava attiva", &default_set.octave , 1, 6);
             break;
    case 16: editSettingT(getMenuTitle(getCurrent_menu(), menu), "tonalita' attiva", &default_set.tonality, lst_tonality);
             break;
    case 17: editSettingT(getMenuTitle(getCurrent_menu(), menu), "forma d'onda", &default_set.waveform, lst_waveform);
             loadWave(wave, default_set.waveform);
             break;
    case 18: editSettingN(getMenuTitle(getCurrent_menu(), menu), "ottava attiva", &default_set.octave , 1, 6);
             break;
    case 19: editSettingT(getMenuTitle(getCurrent_menu(), menu), "tonalita' attiva", &default_set.tonality, lst_tonality);
             break;
    case 20: editSettingN(getMenuTitle(getCurrent_menu(), menu), "canale midi in uso", &default_set.channel, 1, 16);
             midi._canale = default_set.channel-1;
             break;
    case 21: editSettingN(getMenuTitle(getCurrent_menu(), menu), "banco midi attivo", &default_set.patch, 0, 127);
             midi.prgChange(default_set.patch);
             break;
    
    default: break;
  }
}

// ISR
// istruzioni dell'Interrupt Service Routine usate per la generazione di forme d'onda
ISR(TIMER1_COMPA_vect)
{
  /* timer1 ISR.  Every time it is called it sets the speaker pin 
   *  to the next value in playbuffer[].  frequency modulation is done by changing
   *  the timing between successive calls of this function, e.g. for a 1KHz tone,
   *  set the timing so that it runs through playbuffer[] 1000 times a second. */
   
  // reset waveindex if it has reached the end of the array
  if (waveindex > SAMPLE_LEN - 1) 
    waveindex = 0;
  
  // Set timer 2 PWM duty cycle to next value in array. 
  // OCR2B is the register corresponding to duty cycle for PWM pin 3.
  OCR2B = wave[waveindex]; 

  // increment array index
  waveindex++;
  
  // set timer 1 compare match to new value of period.
  OCR1A = period;
}

