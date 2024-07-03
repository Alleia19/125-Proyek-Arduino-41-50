#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define MINPRESSURE 10
#define MAXPRESSURE 1000

const int hCenter = 120;
const int vCenter = 160;
int BS = 10;  //Button Space
int BL = (240/3)-(1.33*BS); //Button Length
int BW = 35; //Button Widh
int TCL = 18; //Text Cursor Length
int SPC = 17; //Space text
long time = 0;
long debounce = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Test Koordinat Touchscreen"));
  tft.reset();
  tft.begin(0x9341); // SDFP5408
  tft.setRotation(0); // Need for the Mega
  tft.fillScreen(BLACK);
  pinMode(13, OUTPUT);
 tft.setTextSize (1);
 tft.setCursor(18,15);
 tft.setTextColor (WHITE);
 tft.print ("Batt:69%      INDOSAT      Sign:90");
 tft.setTextSize (3);
 
  drawButton();
}

void loop() {
   // put your main code here, to run repeatedly:
 //display digit to LCD
    tft.setTextSize(3);
    tft.setCursor(TCL,35);
    tft.setTextColor(CYAN);
  
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  //Touch Button COmmand
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
      
      if (p.x>BS && p.y>100 && p.x<(BS+BL) && p.y<(100+BW)&& millis() - time > debounce) 
      {Serial.print ('A');
      tft.setTextSize(2);
      tft.setCursor(20,63);
      tft.setTextColor(GREEN);
      tft.print("Memanggil..");
      time = millis();}
      if (p.x>BL+(2*BS) && p.y>100 && p.x<((2*BS)+(2*BL)) && p.y<(100+BW)&& millis() - time > debounce) 
      {Serial.print ('B');
      tft.fillRect(20,63,200,17,BLACK);
      tft.setTextSize(2);
      tft.setCursor(20,63);
      tft.setTextColor(RED);
      tft.print("Akhiri Panggilan.");
      delay (2000);
      tft.fillRect(20,63,200,17,BLACK);
      time = millis();}
      if (p.x>((2*BL)+(3*BS)) && p.y>100 && p.x<((3*BS)+(3*BL)) && p.y<(100+BW)&& millis() - time > debounce) 
      {Serial.print ('C');
         if (TCL>18){TCL=TCL-SPC;}
      tft.fillRect(TCL,35,SPC,30,BLACK);
      time = millis();}
      if (p.x>BS && p.y>100+(BW+BS) && p.x<(BS+BL) && p.y<(100+(2*BW)+(1*BS))&& millis() - time > debounce) 
      {Serial.print ('1');
      TCL=TCL+SPC;
      tft.print('1');
      time = millis();}
      if (p.x>BL+(2*BS) && p.y>100+(BW+BS) && p.x<((2*BS)+(2*BL)) && p.y<(100+(2*BW)+(1*BS))&& millis() - time > debounce) 
      {Serial.print ('2');
      TCL=TCL+SPC;
      tft.print('2');
      time = millis();}
      if (p.x>((2*BL)+(3*BS)) && p.y>100+(BW+BS) && p.x<((3*BS)+(3*BL)) && p.y<(100+(2*BW)+(1*BS))&& millis() - time > debounce) 
      {Serial.print ('3');
      TCL=TCL+SPC;
      tft.print('3');
      time = millis();}
      if (p.x>BS && p.y>100+(2*BW)+(2*BS) && p.x<(BS+BL) && p.y<(100+(3*BW)+(2*BS))&& millis() - time > debounce) 
      {Serial.print ('4');
      TCL=TCL+SPC;
      tft.print('4');
      time = millis();}
      if (p.x>BL+(2*BS) && p.y>100+(2*BW)+(2*BS) && p.x<((2*BS)+(2*BL)) && p.y<(100+(3*BW)+(2*BS))&& millis() - time > debounce) 
      {Serial.print ('5');
      TCL=TCL+SPC;
      tft.print('5');
      time = millis();}
      if (p.x>((2*BL)+(3*BS)) && p.y>100+(2*BW)+(2*BS) && p.x<((3*BS)+(3*BL)) && p.y<(100+(3*BW)+(2*BS))&& millis() - time > debounce) 
      {Serial.print ('6');
      TCL=TCL+SPC;
      tft.print('6');
      time = millis();}
      if (p.x>BS && p.y>100+(3*BW)+(3*BS) && p.x<(BS+BL) && p.y<(100+(4*BW)+(3*BS))&& millis() - time > debounce) 
      {Serial.print ('7');
      TCL=TCL+SPC;
      tft.print('7');
      time = millis();}
      if (p.x>BL+(2*BS) && p.y>100+(3*BW)+(3*BS) && p.x<((2*BS)+(2*BL)) && p.y<(100+(4*BW)+(3*BS))&& millis() - time > debounce) 
      {Serial.print ('8');
      TCL=TCL+SPC;
      tft.print('8');
      time = millis();}
      if (p.x>((2*BL)+(3*BS)) && p.y>100+(3*BW)+(3*BS) && p.x<((3*BS)+(3*BL)) && p.y<(100+(4*BW)+(3*BS))&& millis() - time > debounce) 
      {Serial.print ('9');
      TCL=TCL+SPC;
      tft.print('9');
      time = millis();}
      if (p.x>BS && p.y>100+(4*BW)+(4*BS) && p.x<(BS+BL) && p.y<(100+(5*BW)+(4*BS))&& millis() - time > debounce) 
      {Serial.print ('*');
      TCL=TCL+SPC;
      tft.print('*');
      time = millis();}
      if (p.x>BL+(2*BS) && p.y>100+(4*BW)+(4*BS) && p.x<((2*BS)+(2*BL)) && p.y<(100+(5*BW)+(4*BS))&& millis() - time > debounce) 
      {Serial.print ('0');
      TCL=TCL+SPC;
      tft.print('0');
      time = millis();}
      if (p.x>((2*BL)+(3*BS)) && p.y>100+(4*BW)+(4*BS) && p.x<((3*BS)+(3*BL)) && p.y<(100+(5*BW)+(4*BS))&& millis() - time > debounce) 
      {Serial.print ('#');
      TCL=TCL+SPC;
      tft.print('#');
      time = millis();}



    
    
   
}
}
