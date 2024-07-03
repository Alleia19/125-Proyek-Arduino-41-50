/*************************************
 * Program : Project 50. Kalkulator LCD Touch screen
 * Input   : LCD TFT
 * 125 Proyek Arduino Inkubatek
 * www.tokotronik.com
 * ***********************************/
#include <Adafruit_GFX.h>    
#include <Adafruit_TFTLCD.h> 
#include <TouchScreen.h>

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

#define BLACK         0x0000        /*   0,   0,   0 */
#define NAVY          0x000F        /*   0,   0, 128 */
#define DARKGREEN     0x03E0        /*   0, 128,   0 */
#define DARKCYAN      0x03EF        /*   0, 128, 128 */
#define MAROON        0x7800        /* 128,   0,   0 */
#define PURPLE        0x780F        /* 128,   0, 128 */
#define OLIVE         0x7BE0        /* 128, 128,   0 */
#define LIGHTGREY     0xC618        /* 192, 192, 192 */
#define DARKGREY      0x7BEF        /* 128, 128, 128 */
#define BLUE          0x001F        /*   0,   0, 255 */
#define GREEN         0x07E0        /*   0, 255,   0 */
#define CYAN          0x07FF        /*   0, 255, 255 */
#define RED           0xF800        /* 255,   0,   0 */
#define MAGENTA       0xF81F        /* 255,   0, 255 */
#define YELLOW        0xFFE0        /* 255, 255,   0 */
#define WHITE         0xFFFF        /* 255, 255, 255 */
#define ORANGE        0xFD20        /* 255, 165,   0 */
#define GREENYELLOW   0xAFE5        /* 173, 255,  47 */
#define PINK          0xF81F

#define BUTTON_X 40
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 3
#define TEXT_TCOLOR MAGENTA

#define TEXT_LEN 12
char textfield[TEXT_LEN+1] = "";
uint8_t textfield_i=0;
byte f_hitung=0;
String angkaStr="";
long hitung, angka;
long bil1, bil2, hasil;
byte geser, awal;

#define YP A3 
#define XM A2 
#define YM 9  
#define XP 8  

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
#define STATUS_X 10
#define STATUS_Y 65

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button buttons[15];
char buttonlabels[15][5] = {"+", "-", "del", 
                            "1", "2", "3", 
                            "4", "5", "6", 
                            "7", "8", "9", 
                            "=", "0", "C" };
uint16_t buttoncolors[15] = {MAROON, OLIVE, RED, 
                             BLUE,   BLUE,  BLUE, 
                             BLUE,   BLUE,  BLUE, 
                             BLUE,   BLUE,  BLUE, 
                             RED,    BLUE,  RED};
                             
void setup(void) {
  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier==0x0101)identifier=0x9341;
  
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  
  // create buttons
  for (uint8_t row=0; row<5; row++) {
    for (uint8_t col=0; col<3; col++) {
      buttons[col + row*3].initButton(&tft, BUTTON_X+col*(BUTTON_W+BUTTON_SPACING_X), 
      BUTTON_Y+row*(BUTTON_H+BUTTON_SPACING_Y),
      BUTTON_W, BUTTON_H, WHITE, buttoncolors[col+row*3], WHITE,
      buttonlabels[col + row*3], BUTTON_TEXTSIZE); 
      buttons[col + row*3].drawButton();
    }
  }
  
  // Buat text berwarna putih
  tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, WHITE);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop(void) {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

 
   if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
   }
   
  // baca semua tombol apakah ada yang ditekan
  for (uint8_t b=0; b<15; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      //Serial.print("Pressing: "); Serial.println(b);
      buttons[b].press(true);  // tell the button it is pressed
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }

  // now we can ask the buttons if their state has changed
  for (uint8_t b=0; b<15; b++) {
    if (buttons[b].justReleased()) {
      buttons[b].drawButton();  //gambar tombol normal
    }
    
    if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  //gambar tombol dibalik/invert
        
        // Jika tombol yang ditekan bukan +, -, del, =, dan C 
        // maka ambil data array sesuai dengan panjang text
        if ((b != 0) && (b != 1) && (b != 2) && (b != 12) && (b != 14)) {
          if (textfield_i < TEXT_LEN) { 
            textfield[textfield_i] = buttonlabels[b][0];  //ambil data array
            textfield_i++;    //counter jumlah data array
            textfield[textfield_i] = 0; 
          }
        }

        //---- penanganan tombol "del"
        if (b == 2) {          
          textfield[textfield_i] = 0;
          if (textfield_i > 0) {  //jika textfield lebih besar dari nol
            textfield_i--;      //kurangi 1 datanya 
            textfield[textfield_i] = ' '; //isi dengan spasi / kosong
          }
        }
        
        if (f_hitung>0){
          tft.setCursor((TEXT_X + 2)+(geser+18), TEXT_Y+10); 
          tft.setTextColor(TEXT_TCOLOR, BLACK); // BLACK = text block
          tft.setTextSize(TEXT_TSIZE);          //ambil data ukuran text
          tft.print(textfield);         //tampilkan tulisan pada LCD
          tft.print(" ");
          angkaStr=textfield;
          angka=angkaStr.toInt();
          bil2=angka;
        }
        else{
          if(awal==0){ hapusDisplay(); awal=1; }
          tft.setCursor(TEXT_X + 2, TEXT_Y+10); // atur posisi kursor
          tft.setTextColor(TEXT_TCOLOR, BLACK); // BLACK = text block
          tft.setTextSize(TEXT_TSIZE);          //ambil data ukuran text
          tft.print(textfield);         //tampilkan tulisan pada LCD
          tft.print(" ");
          angkaStr=textfield;
          angka=angkaStr.toInt();
          bil1=angka;
        }

        //---- penanganan tombol "+"
        if (b == 0) {
          f_hitung=1;    
          geser=textfield_i*18;
          tft.setCursor((TEXT_X+2)+geser, TEXT_Y+10);
          tft.print('+');     
          for(char i=0;i<textfield_i;i++){
            textfield[i]=' ';
          }
          textfield_i=0; 
        }

        //---- penanganan tombol "-"
        if (b == 1) {
          f_hitung=2;
          geser=textfield_i*18;
          tft.setCursor((TEXT_X+2)+geser, TEXT_Y+10);
          tft.print('-');     
          for(char i=0;i<textfield_i;i++){
            textfield[i]=' ';
          }
          textfield_i=0;
        }
     
        //---- penanganan tombol "="
        if (b == 12) {
          if (f_hitung==1){
            hasil=bil1+bil2;
          }
          else if (f_hitung==2){
            hasil=bil1-bil2;
          }          
          hapusDisplay();
          tft.setCursor(TEXT_X+2, TEXT_Y+10);
          tft.print(hasil);
          f_hitung=0;    
          for(char i=0;i<textfield_i;i++){
            textfield[i]=' ';
          }
          angka=0;
          bil1=0;
          bil2=0;
          awal=0;
          geser=0;
          textfield_i=0;
        }

        //---- penanganan tombol "C" 
        if (b == 14) {      
          for(char i=0;i<textfield_i;i++){
            textfield[i]=' ';
          }
          textfield_i=0;
          geser=0;
          angka=0;
          awal=0;
          hapusDisplay();
        }
                
      delay(200); //debouncing
    }
  }
  
}
void hapusDisplay(){
    tft.fillRect(TEXT_X+2, TEXT_Y+2, TEXT_W-4, TEXT_H-4, BLACK);
}



