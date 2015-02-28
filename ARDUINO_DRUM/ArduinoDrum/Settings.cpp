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
