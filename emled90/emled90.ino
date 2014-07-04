// Code for the Arduino Bike POV project


 // Arduino Bike POV
 //
 // by Scott Mitchell
 // www.openobject.org
 // Open Source Urbanism
 //
 // Copyright (C) 2008 Scott Mitchell 12-10-2008
 //
 // This program is free software: you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation, either version 3 of the License, or
 // (at your option) any later version.
 //
 
 //============================================================
 // 6/2011 heavily modified by c. Dubois for my POV project
 // Hall sensor is a switch so I  used different code for it
 // also used a font.h that I found
 // ------------------------------------------------------------
 
 
 
 
 // defining the alphabet
 #include "font.h"
 
 // define the Arduino LED pins in use
 const int LEDpins[] = {
   22,24,26,28,30,32,34};
 
 // number of LEDs
  const int charHeight = sizeof(LEDpins);
  const int charWidth = 5;
 
 
 
 // sensor setup
 const int sensorPIN = 0;  // define the Arduino sensor pin

//  boolean sensorFlag = false;  // stores sensor state
  int sensVal;  // variable to store the value coming from the sensor
 
 const char textString[] = "APPLAUSE";
 
 void setup()
 {
   pinMode(13, OUTPUT);
    pinMode(1 , OUTPUT);
   pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
     pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
 
   
  //   Serial.begin(9600);
 }
 
 void loop()
 {
   // turn on Led for a circle in middle and proof that arduino is powered
    digitalWrite(13, HIGH);   // set the LED on  
    
     
  sensVal = analogRead(sensorPIN);  // read the Hall Effect Sensor  
 
 
 
 //    Serial.println(sensVal);
// delay(500 );  
// had difficulty here
// since it is a switch hall switch probably shoiuld just do digital read

 if (sensVal  != 1023) {
   // printing every letter of the textString
   for (int k=0; k<sizeof(textString); k++){
     printLetter(textString[k]);
   }

 }
 }
 
 
 
 
 void printLetter(char ch)
 {
   // make sure the character is within the alphabet bounds (defined by the font.h file)
   // if it's not, make it a blank character
   
    
   
   if (ch < 32 || ch > 126){
     ch = 32;
   }
   // subtract the space character (converts the ASCII number to the font index number)
   ch -= 32;
   // step through each byte of the character array
   for (int i=0; i<charWidth; i++) {
     byte b = font[ch][i];
     
 
 
     // bit shift through the byte and output it to the pin
     for (int j=0; j<charHeight; j++) {
       digitalWrite(LEDpins[j], !!(b & (1 << j)));
     
     }
     // space between columns
 
 delayMicroseconds(900);
   }
   //clear the LEDs
 digitalWrite(1 , LOW);   // set the LED on
digitalWrite(2 , LOW);   // set the LED on
digitalWrite(3 , LOW);   // set the LED on
digitalWrite(4 , LOW);   // set the LED on
digitalWrite(5 ,LOW);   // set the LED on
digitalWrite(6 , LOW);   // set the LED on
digitalWrite(7 , LOW);   // set the LED on
   
   // space between letters
   delayMicroseconds(2500);
 
 }
