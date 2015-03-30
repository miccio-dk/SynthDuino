/*
  Synthesis.cpp - Libreria per la sintesi di 
  Riccardo Miccini, Davide Montini - 18/03/2012
  Rilasciata sotto i termini della GNU GPL v3.0 o successive
    
  Alcune parti di codice sono state prese dal progetto "Arduino 
  Theremin/Synth", sviluppato da Max Pierson e rilasciato sotto 
  licenza WTFPL. 
*/

#include "Synthesis.h"

// loadWave
// carica la forma d'onda richiesta n el vettore 'vet'
void loadWave(byte *vet, byte wave)
{
  switch(wave)
  {
    case SINE:    createSin(vet);
                  break;
    case SQUARE:  createSquare(vet);
                  break;
    case RECT:    createRect(vet, 20);
                  break;
    case TRIANG:  createTriang(vet);
                  break;
    case SAW:     createSaw(vet);
                  break;
  }
}

// createSin
// genera un'onda sinusoidale
void createSin(byte *vet)
{
  byte i;
  
  for(i=0;i<SAMPLE_LEN;i++)
    vet[i]=(1+sin((double)i*TWO_PI/SAMPLE_LEN))*SAMPLE_MAX/2;
}

// createSquare
// genera un'onda quadra
void createSquare(byte *vet)
{ 
  byte i;

  for(i=0;i<SAMPLE_LEN;i++)
  {
    if(i<=SAMPLE_LEN/2)
      vet[i]=SAMPLE_MAX;
    else
      vet[i]=0;
  }
}

// createTriang
// genera un'onda triangolare
void createTriang(byte *vet)
{
  byte i;
  double m=(double)SAMPLE_MAX/(SAMPLE_LEN/2);
  
  for(i=0;i<SAMPLE_LEN/2;i++)
     vet[i]= i*m;
  for(i=0;i<SAMPLE_LEN/2;i++)   
     vet[i+SAMPLE_LEN/2]= SAMPLE_MAX-(i*m);
  
}

// createSaw
// genera un'onda a dente di sega
void createSaw(byte *vet)
{
  byte i;
  
  double m=(double)SAMPLE_MAX/SAMPLE_LEN;
  
  for(i=0;i<SAMPLE_LEN;i++)
     vet[i]= i*m;
}

// createRect
// genera un'onda rettangolare, con duty cycle a scelta
void createRect(byte *vet, byte dc)
{
  byte i;
  
  
  for(i=0;i<SAMPLE_LEN;i++)
  {
    if(i<(SAMPLE_LEN*dc/100))
      vet[i]=SAMPLE_MAX;
    else
      vet[i]=0;
   }
}

// initSynth
// inizializza timers e registri configurandoli alla generazione di onde sonore
void initSynth()
{
  pinMode(3, OUTPUT); //Set speaker pin to output
  cli(); //disable interrupts while registers are configured

  bitSet(TCCR2A, WGM20);
  bitSet(TCCR2A, WGM21); //set Timer2 to fast PWM mode (doubles PWM frequency)

  bitSet(TCCR2A, COM2B1);
  /* set pin COM2B (pin3) to toggle on when timer2 overflows, off when a match
   *  is made (non-inverting mode). */

  bitSet(TCCR2B, CS20);
  bitClear(TCCR2B, CS21);
  bitClear(TCCR2B, CS22);
  /* set prescaler to /1 (no prescaling).  The timer will overflow every 
   *  62.5nS * 256ticks = 16uS, giving a PWM frequency of 62,500Hz, I think.   */

  sei(); //enable interrupts now that registers have been set


  /************************* Timer 1 interrupt configuration *************************/

  cli(); //disable interrupts while registers are configured

  bitClear(TCCR1A, COM1A1);
  bitClear(TCCR1A, COM1A1);
  bitClear(TCCR1A, COM1A1);
  bitClear(TCCR1A, COM1A1);
  /* Normal port operation, pins disconnected from timer operation (breaking pwm).  
   *  Should be set this way by default, anyway. */

  bitClear(TCCR1A, WGM10);
  bitClear(TCCR1A, WGM11);
  bitSet(TCCR1B, WGM12);
  bitClear(TCCR1B, WGM13);
  /* Mode 4, CTC with TOP set by register OCR1A.  Allows us to set variable timing for
   *  the interrupt by writing new values to OCR1A. */

  bitSet(TCCR1B, CS10);
  bitClear(TCCR1B, CS11);
  bitClear(TCCR1B, CS12);
  /* set the clock prescaler to /1 (no prescaling.  The timer will increment every 62.5nS.  
   *  Timer 1 is a 16-bit timer, so the maximum value is 65536,
   *  Giving us a theoretical range of 62.5nS-4.096mS.  There are 24 samples, so the 
   *  theoretical frequency range is 667KHz - 10.1Hz, which neatly covers the audio 
   *  spectrum of 20KHz-20Hz.  Theoretical, because I wouldn't recommend actually calling
   *  the Timer1 interrupt every .62.5nS :)  I could have also used the /8 prescaler, 
   *  but this gives better precision. */

  bitClear(TCCR1C, FOC1A);
  bitClear(TCCR1C, FOC1B);
  /* Disable Force Output Compare for Channels A and B, whatever that is.
   *  Should be set this way by default anyway. */

  OCR1A = 160;
  /* Sets Output Compare Register A at 160, so initially a match will be generated 
  *  every 62.5nS * 8 * 160 = 80uS, for a 1/(80uS*48) = 260Hz tone. */

  bitClear(TIMSK1, ICIE1); //disable input capture interrupt
  bitClear(TIMSK1, OCIE1B); //disable Output Compare B Match Interrupt
  bitSet(TIMSK1, OCIE1A); //enable Output Compare A Match Interrupt
  bitClear(TIMSK1, TOIE1); //disable Overflow Interrupt Enable

  sei(); //enable interrupts now that registers have been set
}
