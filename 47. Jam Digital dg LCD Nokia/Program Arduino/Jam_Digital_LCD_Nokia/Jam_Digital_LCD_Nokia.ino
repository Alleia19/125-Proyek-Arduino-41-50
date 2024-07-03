 /*************************************
 * Program : Project 47. Jam Digital dg LCD Nokia
 * 125 Proyek Arduino Inkubatek
 * www.inkubator-teknologi.com
 * www.tokotronik.com
 * ***********************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Wire.h>
#include <DS1307.h>


// Koneksi pin SPI Arduino - LCD Nokia 5110 :
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);



void setup()   {
  Serial.begin(9600);
  display.begin(); 
  display.setContrast(50);
  delay(100);
  RTC.start();
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1); 
  display.println("Jam :"); 
  //------------------------------ 
  display.setTextSize(2);
  display.setCursor(10,10);
  
  display.print(RTC.get(DS1307_HR,true)); //read the hour and also update all the values by pushing in true
  display.print(":");
  display.print(RTC.get(DS1307_MIN,false));//read minutes without update (false)
  
  display.setTextSize(1); 
  display.setCursor(20,35);
  display.print(RTC.get(DS1307_DATE,false)); //read the hour and also update all the values by pushing in true
  display.print("/");
  display.print(RTC.get(DS1307_MTH,false));//
  display.print("/");
  display.print(RTC.get(DS1307_YR,false));//
  display.display();  
  delay(1000);
  
}


