/*
  Settings.cpp - Libreria per la gestione delle impostazioni della batteria
  Riccardo Miccini - 17/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#include "Settings.h"


// editSettingT
// si occupa di gestire la modifica delle impostazioni per liste di opzioni
// title: titolo da mostrare nella prima riga
// descr: descrizione da mostrare nella seconda riga
// val: indirizzo della variabile da modificare
// list[]: array di stringhe contenente i valori da mostrare sullo schermo
void editSettingT(String title, String descr, byte *val, char *list[])
{
  //calcola la lunghezza dell'array
  byte len = 0;
  while(strcmp(list[len],NULL))
    len++;
  
  byte old_val = *val;
  byte act_val = *val;
  byte pre_val = 255;
  byte state = IDLE;
  byte save = 255;
  title.toUpperCase();

  while(save == 255)
  {   
    if(pre_val != act_val)
    {
      menuPrintSetting(title, list[act_val], descr);
      pre_val = act_val;
    }
    state = buttonCheck(A0);
    switch(state)
    {
      case UP:   if(act_val < len-1)
                   act_val++;
                 else
                   act_val = 0;
                 break;
                 
      case DOWN: if(act_val > 0)
                   act_val--;
                 else
                   act_val = len-1;
                 break;
                 
      case SEL:  save = 1;
                 break;
                 
      case BACK: save = 0;
                 break;
    }
  }
  if(state == SEL)
    *val = act_val;
  if(state == BACK)
    *val = old_val;
}

// editSettingN
// si occupa di gestire la modifica delle impostazioni per intervalli di valori
// title: titolo da mostrare nella prima riga
// descr: descrizione da mostrare nella seconda riga
// val: indirizzo della variabile da modificare
// min,max: valore minimo e massimo da mostrare
void editSettingN(String title, String descr, byte *val, byte min, byte max)
{
  byte old_val = *val;
  byte act_val = *val;
  byte pre_val = 0;
  byte state = IDLE;
  byte save = 255;
  title.toUpperCase();
  
  
  while(save == 255)
  {
    if(pre_val != act_val)
    {
      String print_val(act_val);
      print_val = " "+print_val;
      menuPrintSetting(title, print_val, descr);
      pre_val = act_val;
    }
    state = buttonCheck(A0);
    switch(state)
    {
      case UP:   if(act_val < max)
                   act_val++;
                 else
                   act_val = min;
                 break;
                 
      case DOWN: if(act_val > min)
                   act_val--;
                 else
                   act_val = max;
                 break;
                 
      case SEL:  save = 1;
                 break;
                 
      case BACK: save = 0;
                 break;
    }
  }
  if(state == SEL)
    *val = act_val;
  if(state == BACK)
    *val = old_val;
}

// chosePad
// permette di scegliere il pad da configurare
byte chosePad()
{
  byte act_val = 1;
  byte pre_val = 0;
  byte state = IDLE;
  byte stay = true;  
  
  while(stay == true)
  {
    if(pre_val != act_val)
    {
      String print_val(act_val);
      print_val = " "+print_val;
      menuPrintSetting("IMPOSTAZIONI PAD", print_val, "scegli pad:");
      pre_val = act_val;
    }
    state = buttonCheck(A0);
    switch(state)
    {
      case UP:   if(act_val < 8)
                   act_val++;
                 else
                   act_val = 1;
                 break;
                 
      case DOWN: if(act_val > 1)
                   act_val--;
                 else
                   act_val = 8;
                 break;
                 
      case SEL:  stay = false;
                 break;
                 
      case BACK: stay = false;
                 break;
    }
  }
  if(state == SEL)
    return act_val;
  if(state == BACK)
    return 255;
}

// editPadSettings
// permette di configurare il pad selezionato
void editPadSettings(PadSetting *set, byte n_pad)
{
  byte old_note = set->note;
  byte act_note = set->note;
  byte pre_note = -1;

  byte old_vel = set->velocity;
  byte act_vel = set->velocity;
  byte pre_vel = -1;  
  
  byte state = IDLE;
  byte change = true;
  byte submenu = NOTE;
  
  String title("IMP. PAD #");
  title = title+n_pad;
  
  while(change == true)
  {
    if(pre_note!=act_note || pre_vel!=act_vel)
    {
      String print_note(act_note);
      String print_vel(act_vel);
      
      if(submenu == NOTE)
        print_note = "- nota midi: "+print_note;
      else
        print_note = "  nota midi: "+print_note;
      
      if(submenu == VELO)
        print_vel = "- velocity: "+print_vel;
      else
        print_vel = "  velocity: "+print_vel;
      
      menuPrint2Settings(title, print_note, print_vel);
      pre_note = act_note;
      pre_vel = act_vel;
    }
    state = buttonCheck(A0);
    
    switch(submenu)
    {
      case NOTE:  switch(state)
                  {
                    case UP:   if(act_note < 127)
                                 act_note++;
                               else
                                 act_note = 0;
                               break;
                               
                    case DOWN: if(act_note > 0)
                                 act_note--;
                               else
                                 act_note = 127;
                               break;
                               
                    case SEL:  submenu = VELO;
                               break;
                               
                    case BACK: change = false;
                               break;
                  }
                  break;
                  
      case VELO:  switch(state)
                  {
                    case UP:   if(act_vel < 127)
                                 act_vel++;
                               else
                                 act_vel = 0;
                               break;
                               
                    case DOWN: if(act_vel > 0)
                                 act_vel--;
                               else
                                 act_vel = 127;
                               break;
                               
                    case SEL:  change = false;
                               break;
                               
                    case BACK: submenu = NOTE;
                               break;
                  }
                  break;
    }
  }
  
  if(state == SEL)
  {
    set->note = act_note;
    set->velocity = act_vel;
  }
 
  if(state == BACK)
  {
    set->note = old_note;
    set->velocity = old_vel;
  }
}
