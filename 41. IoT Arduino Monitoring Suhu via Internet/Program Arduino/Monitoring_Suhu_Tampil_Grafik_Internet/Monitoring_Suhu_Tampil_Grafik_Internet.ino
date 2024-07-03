/*************************************
 * Program : Project 41. IoT Arduino Monitoring Suhu via Internet
 * Input   : Sensor , Tombol push
 * Output  : LCD 2x16, BUZZER, Relay
 * 125 Proyek Arduino Inkubatek
 * www.tokotronik.com
 * ***********************************/
#define BLYNK_PRINT Serial 
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>

int adc0;
int outputpin= A0;
float celcius,millivolts;

char auth[] = "d0a7bde2ea5c47b5ab57b9a6c6732229";
// Sesuaikan dengan ssid dan password hotspot anda
char ssid[] = "TokotronikWiFi";
char pass[] = "inkubatek";
SoftwareSerial EspSerial(2, 3); // RX, TX
#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

void setup()
{
  Serial.begin(9600); 
  EspSerial.begin(9600);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);   
}

void sendData()
{   
  adc0 = analogRead(outputpin);
  millivolts = (adc0/1024.0) * 5000; 
  celcius = millivolts/10;
  Serial.println(celcius);
  Blynk.virtualWrite(0, celcius);//virtual input V10 di Blynk (suhu) 
}

void loop()
{
  Blynk.run();
  delay(1000);
  sendData();
}
