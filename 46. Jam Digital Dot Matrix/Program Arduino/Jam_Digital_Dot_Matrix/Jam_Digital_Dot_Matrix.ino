/*************************************
 * Program : Project 46. Jam Digital Dot Matrix
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
char str[12];

//===============================================================
void printText(uint8_t modStart, uint8_t modEnd, char *pMsg)
{
 uint8_t   state = 0;
 uint8_t   curLen;
 uint16_t  showLen;
 uint8_t   cBuf[8];
 int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;

 mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

 do     
 {
   switch(state)
   {
     case 0:   
      
       if (*pMsg == '\0')
       {
         showLen = col - (modEnd * COL_SIZE);  // padding characters
         state = 2;
         break;
       }

       
       showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
       curLen = 0;
       state++;      

     case 1:    
       mx.setColumn(col--, cBuf[curLen++]);

       
       if (curLen == showLen)  
       {
         showLen = CHAR_SPACING;
         state = 2;
       }
       break;

     case 2: 
       curLen = 0;
       state++;
       // fall through

     case 3:    
       mx.setColumn(col--, 0);
       curLen++;
       if (curLen == showLen) 
         state = 0;
       break;

     default:
       col = -1;   
   }
 } while (col >= (modStart * COL_SIZE));

 mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void setup()
{
 mx.begin(); 
 delay(1000); 
}

void loop() 
{ 
  //------------------------------ baca jam & menit  
  char h(RTC.get(DS1307_HR,true));
  char m(RTC.get(DS1307_MIN,false));  
  //------------------------------ 
  sprintf(str," %d:%d",h,m);
  printText(0, MAX_DEVICES-1,str);   
  delay(900); 
}
