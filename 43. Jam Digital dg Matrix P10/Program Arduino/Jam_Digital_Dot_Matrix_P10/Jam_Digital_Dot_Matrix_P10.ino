/*************************************
 * Program : Project 43. Jam Digital dg Matrix P10
 * 125 Proyek Arduino Inkubatek
 * www.inkubator-teknologi.com
 * www.tokotronik.com
 * ***********************************/

#include <Wire.h>
#include <DS1307.h> 
#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
int a;
char b[8];
String str;

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}


void setup()
{ 
 
  RTC.stop();    
  RTC.start();
  Serial.begin(9600);
  Timer1.initialize( 5000 );           
  Timer1.attachInterrupt( ScanDMD );
  dmd.clearScreen( true );
}

void loop()
{
  str="";
  int h(RTC.get(DS1307_HR,true));
  int m(RTC.get(DS1307_MIN,false));  
  dmd.clearScreen( true );    
  str=String(h)+":"+String(m);
  str.toCharArray(b,6);  
  dmd.selectFont(SystemFont5x7);  
  dmd.drawString( 1, 4, b, 5, GRAPHICS_NORMAL );  
  delay(5000);   

}


