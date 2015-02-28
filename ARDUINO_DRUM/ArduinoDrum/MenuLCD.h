/*
  MenuLCD.h - Libreria per la gestione del display e del menù
  Riccardo Miccini - 17/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#ifndef MenuLCD_H
#define MenuLCD_H

#include "Arduino.h"
#include <LiquidCrystal.h>

// identificatori degli stati (bottoni e stato di idle)
#define UP   0
#define DOWN 6
#define SEL  2
#define BACK 4
#define IDLE 10

// database menù
typedef struct
{
  byte id;        // PK: identificatore univoco della voce
  byte id_par;    // FK: riferimento al menu genitore della voce
  char str[18];   // stringa contenente il testo visualizzato
} MenuItem;

// funzioni
void initDisplay();
void menuPrint(byte submenu, byte sel, MenuItem *menu);
void menuPrintSetting(String title, String val, String descr);
byte getFirstOption(byte submenu, MenuItem *menu);
byte getLastOption(byte submenu, MenuItem *menu);
byte getPreviousMenu(byte submenu, MenuItem *menu);
String getMenuTitle(byte submenu, MenuItem *menu);
byte buttonCheck(byte pin);
void showIntro();
// setters
void setMenu_lenght(byte n);
void setCurrent_menu(byte n);
void setCurrent_sel(byte n);
void setSthToDo(boolean n);
// getters
byte getCurrent_menu();
byte getCurrent_sel();
boolean getSthToDo();
// comparatori, ritornano true se la variabile e la sua "old" sono diverse
boolean cmpCurrent_menu();
boolean cmpCurrent_sel();
boolean cmpSthToDo();
// aggiorna le variabili "old"
void updateAll();


#endif
