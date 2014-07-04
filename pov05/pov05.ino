//simple POV display with 7 leds and 1 tilt sensor
//by phil (www.telalab.org) philteta@gmail.com
//7x5 ascii font from TVout Lib
// version 0.5

#include "font7x5.h"
#include <avr/pgmspace.h>

int delinterchar = 800 ;//delay between 2 char
int delinterpoint = 400; //delay between 2 points of a char

#define led1 22
#define led2 24
#define led3 26
#define led4 28
#define led5 30
#define led6 32
#define led7 34
#define sensorPin 2
#define policex 5
#define nbleds 7
int boucle = 0;
#define repet 10 //number of repetition before changing message
char texte[]  = "TETALAB"; // data to write on startup
char texte2[] = "BEER INSIDE"; // data to write after "repet" writing of the first message
unsigned long lasttimeloop;
unsigned long timeloop;


int a = 0;
int leds[nbleds] = {
  led1,led2,led3,led4,led5,led6,led7};

void setup()   
{                
  for (byte i=0;i<nbleds;i++)
  {
      pinMode(leds[i], OUTPUT);     
  }

  lasttimeloop = micros();
}

void alloff()
{
  for (byte i=0;i<nbleds;i++)
  {
     digitalWrite(leds[i], LOW);  
  }
}


void loop()                     
{
  if (digitalRead(2)==LOW) //tilt sensor triggerd
  {
    timeloop = micros() - lasttimeloop; //time between two "shakes"
    lasttimeloop = micros();
    if (timeloop>5000000) timeloop = 1000000; //limitation for loop time
    delay(50);

    if (boucle< (repet + 1))
    {
      delinterchar = timeloop/(sizeof(texte)*policex*policex);
      delinterpoint = delinterchar/2;
      for (a=0;a<sizeof(texte)-1;a++)
      {
        displayChar(texte[a]);
        alloff();
        delayMicroseconds(delinterchar);
      }
    }

    if (boucle>repet)
    {
      delinterchar = timeloop/(sizeof(texte2)*policex*policex);
      delinterpoint = delinterchar/2;
      for (a=0;a<sizeof(texte2)-1;a++)
      {
        displayChar(texte2[a]);
        alloff();
        delayMicroseconds(delinterchar);
      }
    }
    boucle++;
    if (boucle> ((repet*2)+1)) boucle = 0;
  }
}

void displayChar(char c)
{
  c = c - 32;
  for (int i = 7;i>2;i--)
  {
    for (int j = 0;j<7;j++) 
    {
      if (bitRead(pgm_read_byte_near(charbook + (7*c+j)),i) == 1)  digitalWrite(leds[j], HIGH);
      else digitalWrite(leds[j], LOW);
    }
    delayMicroseconds(delinterpoint);
  }
}

