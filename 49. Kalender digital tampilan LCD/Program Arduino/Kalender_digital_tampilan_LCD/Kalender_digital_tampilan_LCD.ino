/*************************************
 * Program : Project 49. Kalender digital tampilan LCD
 * 125 Proyek Arduino Inkubatek
 * www.inkubator-teknologi.com
 * www.tokotronik.com
 * ***********************************/
#include <LiquidCrystal.h>
#include "Wire.h"
#define DS1307_ADDRESS 0x68
byte zero = 0x00;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int menu;
byte second ,minute,hour, weekDay;
byte monthDay,month,year;

boolean up=false;
boolean down=false;

void setup(){
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH); 
  digitalWrite(11,HIGH);  
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Kalender digital");  
  delay(2000);
  lcd.clear();
}

void loop(){
  bacaRTC();
  lcdDisplay();
  cekTombol();
  delay(1000);
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

void cekTombol(){
  if (digitalRead(8)==0){
    lcd.clear();
    lcd.print("Seting RTC");
    delay(2000);
    menu++;
    lcd.clear();
    lcdDisplay();
    lcd.blink();
    do{
      //------------------------next
      if (digitalRead(8)==0){
        delay(300);
        menu++;
      }
      //--------------------back
      else if (digitalRead(9)==0){
        delay(300);
        if (menu > 1){
         menu--;
        }
      }
      //---------------------------up
      else if(digitalRead(10)==0){
        delay(200);
        up=true;
      }
    
  //----------------------------down      
      else if(digitalRead(11)==0){
        delay(200);
        down=true;
      }
 //-------------------------edit data jam       
      if (menu==1){
        if (up==true && hour < 24){
            hour++;
            lcdDisplay();
        }
        else if (down==true && hour>0){
            hour--;
            lcdDisplay();
        }
        up=false;
        down=false;
        if (hour<10){            
          lcd.setCursor(5,0);
        }
        else  {         
          lcd.setCursor(6,0);
        }
      }
        
 //-------------------------edit data menit
      else if (menu==2){      
        if (up==true && minute < 59){   
            minute++;
            lcdDisplay();
          }
        else if (down==true && minute>0){
           minute--;
           lcdDisplay();
        }
           up=false;
           down=false;
           
        if (hour<10 && minute<10){            
          lcd.setCursor(7,0);
        }
        else if (hour<10 && minute>9){          
          lcd.setCursor(8,0);
        }
        else if (hour>9 && minute<10){            
          lcd.setCursor(8,0);
        }
        else if (hour>9 && minute>9){        
          lcd.setCursor(9,0);
        }
      }
        
 //-------------------------edit data detik  
      else if (menu==3){
        if (up==true && second < 59){   
            second++;
            lcdDisplay();
          }
        else if (down==true && second>0){
           second--;
           lcdDisplay();
        }
        up=false;
        down=false;
           
        if (hour<10 && minute<10 && second<10){            
          lcd.setCursor(9,0);
        }
        else if (hour<10 && minute<10 && second>9){          
          lcd.setCursor(10,0);
        }
        else if (hour<10 && minute>9 && second<10){          
          lcd.setCursor(10,0);
        }
        else if (hour>9 && minute<10 && second<10){          
          lcd.setCursor(10,0);
        }
        else if (hour<10 && minute>9 && second>9){          
          lcd.setCursor(11,0);
        }
        else if (hour>9 && minute>9 && second<10){          
          lcd.setCursor(11,0);
        }
        else if (hour>9 && minute<10 && second>9){          
          lcd.setCursor(11,0);
        }
        else if (hour>9 && minute>9 && second>9){          
          lcd.setCursor(12,0);
        }
      }
      
 //-------------------------edit data hari  
      else if (menu==4){
        if (up==true && weekDay < 6){
            weekDay++;
            lcdDisplay();
        }
        else if (down==true && weekDay>0){
            weekDay--;
            lcdDisplay();
        }
        up=false;
        down=false;           
        lcd.setCursor(0,1);
      }
      
 //-------------------------edit data tanggal 
      else if (menu==5){        
        if (up==true && monthDay < 31){
            monthDay++;
            lcdDisplay();
        }
        else if (down==true && monthDay>1){
            monthDay--;
            lcdDisplay();
        }
        up=false;
        down=false;         
        if (monthDay<10){            
          lcd.setCursor(5,1);
        }
        else  {         
          lcd.setCursor(6,1);
        }        
      }
      
 //-------------------------edit data bulan
      else if (menu==6){      
        if (up==true && month < 12){   
            month++;
            lcdDisplay();
          }
        else if (down==true && month>1){
           month--;
           lcdDisplay();
        }
           up=false;
           down=false;
           
        if (monthDay<10 && month<10){            
          lcd.setCursor(7,1);
        }
        else if (monthDay<10 && month>9){          
          lcd.setCursor(8,1);
        }
        else if (monthDay>9 && month<10){            
          lcd.setCursor(8,1);
        }
        else if (monthDay>9 && month>9){        
          lcd.setCursor(9,1);
        }
      }
      
 //-------------------------edit data tahun
      else if (menu==7){
        if (up==true && year < 99){   
            year++;
            lcdDisplay();
          }
        else if (down==true && year>0){
           year--;
           lcdDisplay();
        }
        up=false;
        down=false;
           
        if (monthDay<10 && month<10 && year<10){            
          lcd.setCursor(11,1);
        }
        else if (monthDay<10 && month<10 && year>9){          
          lcd.setCursor(12,1);
        }
        else if (monthDay<10 && month>9 && year<10){          
          lcd.setCursor(12,1);
        }
        else if (monthDay>9 && month<10 && year<10){          
          lcd.setCursor(12,1);
        }
        else if (monthDay<10 && month>9 && year>9){          
          lcd.setCursor(13,1);
        }
        else if (monthDay>9 && month>9 && year<10){          
          lcd.setCursor(13,1);
        }
        else if (monthDay>9 && month<10 && year>9){          
          lcd.setCursor(13,1);
        }
        else if (monthDay>9 && month>9 && year>9){          
          lcd.setCursor(14,1);
        }
      }
      
 //-------------------------simpan data RTC  
      if (menu==8)setingRTC();
    }
    while(menu < 8);
    lcd.clear();
    lcd.noBlink();
    lcd.print("Seting RTC OK!");
    delay(1000);
    lcd.clear();
    menu=0;
  }
}

void lcdDisplay(){
  lcd.setCursor(0,0);
  lcd.print("Jam:");
  lcd.setCursor(5,0);
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);
  lcd.print(":");
  lcd.print(second);
  lcd.print("    ");
      
  lcd.setCursor(0,1);
  hari();
  lcd.setCursor(5,1);
  lcd.print(monthDay);
  lcd.print("/");
  lcd.print(month);
  lcd.print("/20");
  lcd.print(year);
  lcd.print("    ");
}  

void hari(){
  if (weekDay==0){
    lcd.print("Ming, ");
  }
  else if (weekDay==1){
    lcd.print("Sen,");
  }
  else if (weekDay==2){
    lcd.print("Sel,");
  }
  else if (weekDay==3){
    lcd.print("Rab,");
  }
  else if (weekDay==4){
    lcd.print("Kam,");
  }
  else if (weekDay==5){
    lcd.print("Jum,");
  }
  else if (weekDay==6){
    lcd.print("Sab,");
  }
}

void setingRTC(){
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //stop RTC
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekDay));
  Wire.write(decToBcd(monthDay));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(zero); //start 
  Wire.endTransmission();
}


