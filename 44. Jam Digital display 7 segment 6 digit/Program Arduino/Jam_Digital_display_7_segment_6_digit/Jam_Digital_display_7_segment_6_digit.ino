/*************************************
 * Program : Project 44. Jam Digital display 7 segment 6 digit
 * 125 Proyek Arduino Inkubatek
 * www.inkubator-teknologi.com
 * www.tokotronik.com
 * ***********************************/
#include <LiquidCrystal.h>
#include <Wire.h>
#define DS1307_ADDRESS 0x68
byte zero = 0x00;

byte nilai,i;
byte second ,minute,hour, weekDay;
byte monthDay,month,year;

byte seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1 },  // = 0
                                 { 1,0,0,1,1,1,1 },  // = 1
                                 { 0,0,1,0,0,1,0 },  // = 2
                                 { 0,0,0,0,1,1,0 },  // = 3
                                 { 1,0,0,1,1,0,0 },  // = 4
                                 { 0,1,0,0,1,0,0 },  // = 5
                                 { 0,1,0,0,0,0,0 },  // = 6
                                 { 0,0,0,1,1,1,1 },  // = 7
                                 { 0,0,0,0,0,0,0 },  // = 8
                                 { 0,0,0,0,1,0,0 }   // = 9
                               };

void setup()
{
  pinMode(2, OUTPUT); //a 
  pinMode(3, OUTPUT);//b
  pinMode(4, OUTPUT);//c
  pinMode(5, OUTPUT);//d
  pinMode(6, OUTPUT);//e
  pinMode(7, OUTPUT);//f
  pinMode(8, OUTPUT);//g
  pinMode(9, OUTPUT);//dig 1 
  pinMode(10, OUTPUT);//dig 2 
  pinMode(11, OUTPUT);//dig 3 
  pinMode(12, OUTPUT);//dig 4
  pinMode(13, OUTPUT);//dig 5 
  pinMode(A0, OUTPUT);//dig 6
  Wire.begin();
/*---------seting jam
  second = 5; //0-59
  minute = 36; //0-59
  hour = 11; //0-23
  setingRTC();
---------------------*/  
}
void loop(){  
  bacaRTC();
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(A0,HIGH);
  sevenSegWrite(hour/10);
  delay(3);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(A0,HIGH);
  sevenSegWrite(hour%10);
  delay(3);  
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(A0,HIGH);
  sevenSegWrite(minute/10);
  delay(3);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(A0,HIGH);
  sevenSegWrite(minute%10);
  delay(3);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  digitalWrite(A0,HIGH);
  sevenSegWrite(second/10);
  delay(3);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(A0,LOW);
  sevenSegWrite(second%10);
  delay(3);  
}

void sevenSegWrite(byte segment) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[segment][segCount]);
    ++pin;
  }
}

byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
  return ( (val/16*10) + (val%16) );
}

void bacaRTC(){
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0b111111);
  weekDay = bcdToDec(Wire.read());
  monthDay = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

void setingRTC(){
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //stop RTC
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(zero); //start 
  Wire.endTransmission();
}

