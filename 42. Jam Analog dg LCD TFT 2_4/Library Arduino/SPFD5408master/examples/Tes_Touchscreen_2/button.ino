void drawButton () {
tft.drawRoundRect(BS,7,240-(2*BS),80,10,WHITE);
  
tft.drawRoundRect(BS,100,BL,BW,5,WHITE);
tft.setTextColor(GREEN);
tft.setCursor(BS+(0.13*BL),100+(0.2*BW));
tft.print("YES");
tft.drawRoundRect(BL+(2*BS),100,BL,BW,5,WHITE);
tft.setTextColor(RED);
tft.setCursor(BL+(2*BS)+(0.25*BL),100+(0.2*BW));
tft.print("NO");
tft.drawRoundRect((2*BL)+(3*BS),100,BL,BW,5,WHITE);
tft.setTextColor(YELLOW);
tft.setCursor((2*BL)+(3*BS)+(0.13*BL),100+(0.2*BW));
tft.print("DEL");

tft.setTextColor(BLUE);
tft.drawRoundRect(BS,100+(BW+BS),BL,BW,5,WHITE);
tft.setCursor(BS+(0.4*BL),100+(BW+BS)+(0.2*BW));
tft.print('1');

tft.drawRoundRect(BL+(2*BS),100+(BW+BS),BL,BW,5,WHITE);
tft.setCursor(BL+(2*BS)+(0.4*BL),100+(BW+BS)+(0.2*BW));
tft.print('2');

tft.drawRoundRect((2*BL)+(3*BS),100+(BW+BS),BL,BW,5,WHITE);
tft.setCursor((2*BL)+(3*BS)+(0.4*BL),100+(BW+BS)+(0.2*BW));
tft.print('3');

tft.drawRoundRect(BS,100+(2*BW)+(2*BS),BL,BW,5,WHITE);
tft.setCursor(BS+(0.4*BL),100+(2*BW)+(2*BS)+(0.2*BW));
tft.print('4');
tft.drawRoundRect(BL+(2*BS),100+(2*BW)+(2*BS),BL,BW,5,WHITE);
tft.setCursor(BL+(2*BS)+(0.4*BL),100+(2*BW)+(2*BS)+(0.2*BW));
tft.print('5');
tft.drawRoundRect((2*BL)+(3*BS),100+(2*BW)+(2*BS),BL,BW,5,WHITE);
tft.setCursor((2*BL)+(3*BS)+(0.4*BL),100+(2*BW)+(2*BS)+(0.2*BW));
tft.print('6');


tft.drawRoundRect(BS,100+(3*BW)+(3*BS),BL,BW,5,WHITE);
tft.setCursor(BS+(0.4*BL),100+(3*BW)+(3*BS)+(0.2*BW));
tft.print('7');
tft.drawRoundRect(BL+(2*BS),100+(3*BW)+(3*BS),BL,BW,5,WHITE);
tft.setCursor(BL+(2*BS)+(0.4*BL),100+(3*BW)+(3*BS)+(0.2*BW));
tft.print('8');
tft.drawRoundRect((2*BL)+(3*BS),100+(3*BW)+(3*BS),BL,BW,5,WHITE);
tft.setCursor((2*BL)+(3*BS)+(0.4*BL),100+(3*BW)+(3*BS)+(0.2*BW));
tft.print('9');


tft.drawRoundRect(BS,100+(4*BW)+(4*BS),BL,BW,5,WHITE);
tft.setCursor(BS+(0.4*BL),100+(4*BW)+(4*BS)+(0.2*BW));
tft.print('*');
tft.drawRoundRect(BL+(2*BS),100+(4*BW)+(4*BS),BL,BW,5,WHITE);
tft.setCursor(BL+(2*BS)+(0.4*BL),100+(4*BW)+(4*BS)+(0.2*BW));
tft.print('0');
tft.drawRoundRect((2*BL)+(3*BS),100+(4*BW)+(4*BS),BL,BW,5,WHITE);
tft.setCursor((2*BL)+(3*BS)+(0.4*BL),100+(4*BW)+(4*BS)+(0.2*BW));
tft.print('#');
  
}

