/*************************************
 * Program : Project 48. Kalender Digital Animasi Dot Matrix
 * 125 Proyek Arduino Inkubatek
 * www.inkubator-teknologi.com
 * www.tokotronik.com
 * ***********************************/
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>
#include <DS1307.h>

#define    MAX_DEVICES    4
#define    CLK_PIN        13  // or SCK
#define    DATA_PIN    11  // or MOSI
#define    CS_PIN        10  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);
#define    CHAR_SPACING    1    // pixels between characters
#define    BUF_SIZE    75
#define UNIT_DELAY      25
#define SCROLL_DELAY    (4 * UNIT_DELAY)

static  boolean bRestart = true;
uint32_t prevTimeAnim = 0;    
char str[30];

//==============================
bool scrollText(bool bInit, char *pmsg)
// Callback function for data that is required for scrolling into the display
{
  static char    curMessage[BUF_SIZE];
  static char   *p = curMessage;
  static uint8_t  state = 0;
  static uint8_t  curLen, showLen;
  static uint8_t  cBuf[8];
  uint8_t         colData;

  // are we initializing?
  if (bInit)
  {    
    resetMatrix();
    strcpy(curMessage, pmsg);
    state = 0;
    p = curMessage;
    bInit = false;
  }

  // Is it time to scroll the text?
  if (millis()-prevTimeAnim < SCROLL_DELAY)
    return(bInit);

  // scroll the display
  mx.transform(MD_MAX72XX::TSL);  // scroll along
  prevTimeAnim = millis();      // starting point for next time

  // now run the finite state machine to control what we do 
  switch (state)
  {
    case 0: // Load the next character from the font table     
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
      curLen = 0;
      state = 1;
    case 1: // display the next part of the character
      colData = cBuf[curLen++];
      mx.setColumn(0, colData);
      if (curLen == showLen)
      {
        showLen = ((*p != '\0') ? CHAR_SPACING : mx.getColumnCount()-1);
        curLen = 0;
        state = 2;
      }
      break;

    case 2: // display inter-character spacing (blank column) or scroll off the display
      mx.setColumn(0, 0);
      if (++curLen == showLen) 
      {
        state = 0;
        bInit = (*p == '\0');
      }
      break;
    default:
      state = 0;
  }
  return(bInit);
}
//==============

void setup()
{
 mx.begin(); 
 delay(1000); 
}

void loop() 
{ 
  //------------------------------ baca jam, menit, tanggal  
  char h(RTC.get(DS1307_HR,true));
  char m(RTC.get(DS1307_MIN,false));  
  char d(RTC.get(DS1307_DATE,false));  
  char t(RTC.get(DS1307_MTH,false));  
  word y(RTC.get(DS1307_YR,false));  
  //------------------------------ 
  sprintf(str,"Tgl=%d/%d/%d Jam=%d:%d",d,t,y,h,m);
  bRestart = scrollText(bRestart, str); 
}

//==================================
void resetMatrix(void)
{
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  prevTimeAnim = 0;
}
