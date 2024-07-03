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

#define  BLACK   0x0000
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

int px=0, py=0, pz=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Test Koordinat Touchscreen"));
  tft.reset();
  tft.begin(0x9341); // SDFP5408
  tft.setRotation(0); // Need for the Mega
  tft.fillScreen(BLACK);
  tft.setTextSize (3);
  pinMode(13, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);

    tft.setCursor(70,120);
    tft.fillRect(105,120,55,25,BLACK);
    tft.setTextColor(RED);
    tft.print("X:");
    tft.print(p.x);
    px = p.x;

    tft.setCursor(70,150);
    tft.fillRect(105,150,55,25,BLACK);
    tft.setTextColor(GREEN);
    tft.print("Y:");
    tft.print(p.y);
    py = p.y;

    tft.setCursor(70,180);
    tft.fillRect(105,180,55,25,BLACK);
    tft.setTextColor(BLUE);
    tft.print("Z:");
    tft.print(p.z);
    pz = p.z;
}
}
