/*
  MenuLCD.cpp - Libreria per la gestione del display e del menù
  Riccardo Miccini - 17/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
*/

#include "MenuLCD.h"

// informazioni del carattere di selezione
byte sel_dot[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000,
};

// variabili di servizio
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte menu_lenght;            // Numero di voci del menu
byte current_menu = 0;       // Menu corrente
byte current_sel = 1;        // Voce attualmente selezionata
boolean sthToDo = false;     // Necessità di eseguire azioni
byte old_menu = 255;         // Menu precedente
byte old_sel = 255;          // Voce precedentemente selezionata
boolean old_sthToDo = false; // Stato precedente di sthToDo

// initDisplay
// inizializza lo schermo e il carattere di selezione
void initDisplay()
{
  lcd.begin(20, 4);
  lcd.createChar(1, sel_dot);
}

// menuPrint
// stampa il menù sul display
// submenu: id del menu da stampare
// sel: id della voce da evidenziare
void menuPrint(byte submenu, byte sel, MenuItem *menu)
{
  byte screen_line = 0;
  byte i;
  String titolo;
  
  lcd.clear();
  lcd.setCursor(0, screen_line);
  for(i=0; i<menu_lenght; i++)
  {
    if(menu[i].id == submenu)
    {
      titolo=menu[i].str;
      titolo.toUpperCase();
      lcd.print(titolo);
      screen_line++;
    }
    
    if(menu[i].id_par == submenu)
    {
      if(menu[i].id == sel)
      {
        lcd.setCursor(0, screen_line);
        lcd.write(1);
        lcd.print(" ");
        lcd.print(menu[i].str);
      }
      else
      {
        lcd.setCursor(2, screen_line);
        lcd.print(menu[i].str);
      }
      screen_line++;
    }
  }
}

// menuPrintSetting
// stampa la schermata della modifica delle impostazioni
void menuPrintSetting(String title, String val, String descr)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(title);
  lcd.setCursor(0, 1);
  lcd.print(descr);
  lcd.setCursor(0, 2);
  lcd.print(" <##            ##> ");
  lcd.setCursor(7, 2);
  lcd.print(val);
}


// menuPrint2Settings
// stampa la schermata della modifica di due impostazioni (usata dai pad)
void menuPrint2Settings(String title, String val1, String val2)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(title);
  lcd.setCursor(0, 1);
  lcd.print(val1);
  lcd.setCursor(0, 2);
  lcd.print(val2);
}


// getFirstOption
// restituisce l'id della prima voce del menu
byte getFirstOption(byte submenu, MenuItem *menu)
{
  byte i;
  for(i=0; i<menu_lenght; i++)
    if(menu[i].id_par == submenu)
      return menu[i].id;
  return submenu;
}

// getLastOption
// restituisce l'id dell'ultima voce del menu
byte getLastOption(byte submenu, MenuItem *menu)
{
  byte i;
  for(i=0; i<menu_lenght; i++)
    if(menu[menu_lenght-i-1].id_par == submenu)
      return menu[menu_lenght-i-1].id;
  return submenu;
}

// getPreviousMenu
// restituisce l'id del menu genitore
byte getPreviousMenu(byte submenu, MenuItem *menu)
{
  byte i;
  for(i=0; i<menu_lenght; i++)
    if(menu[i].id == submenu)
      return (menu[i].id_par);
  return submenu;
}

// getMenuTitle
// restituisce la stringa con il titolo del menu selezionato
String getMenuTitle(byte submenu, MenuItem *menu)
{
  byte i;
  for(i=0; i<menu_lenght; i++)
    if(menu[i].id == submenu)
      return (menu[i].str);
  return 0;
}

// buttonCheck
// restituisce l'identificatore dello stato della pulsantiera
byte buttonCheck(byte pin)
{
  byte val = analogRead(pin)/100;
  if(val != IDLE)
  {
    while(analogRead(pin)/100 == val){}
    return val;
  }
  return IDLE;
}

// showIntro
// schermata iniziale (uscire premendo SEL)
void showIntro()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("##################### ARDUINO DRUM 0.2 #");
  lcd.print("# Riccardo Miccini #####################");
  while(buttonCheck(0) != SEL){}
}

// showText
// mostra un
void showText(String str1, String str2, String str3, String str4)
{
  byte i;
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print(str1);
  lcd.setCursor(0, 1);
  lcd.print(str2);
  lcd.setCursor(0, 2);
  lcd.print(str3);
  lcd.setCursor(0, 3);
  lcd.print(str4);
}

// Funzioni Varie
// setters, getters, comparatori e aggiornatore
void setMenu_lenght(byte n){
  menu_lenght=n;
}

void setCurrent_menu(byte n){
  current_menu=n;
}

void setCurrent_sel(byte n){
  current_sel=n;
}

void setSthToDo(boolean n){
  sthToDo=n;
}


byte getCurrent_menu(){
  return current_menu;
}

byte getCurrent_sel(){
  return current_sel;
}

boolean getSthToDo(){
  return sthToDo;
}


boolean cmpCurrent_menu(){
  return current_menu!=old_menu;
}

boolean cmpCurrent_sel(){
  return current_sel!=old_sel;
}

boolean cmpSthToDo(){
  return sthToDo!=old_sthToDo;
}

void updateAll()
{
  old_sthToDo = sthToDo;
  old_menu = current_menu;
  old_sel = current_sel;
}
