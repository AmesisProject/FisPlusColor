void Display_2(){

  tft.fillRectangle(0, 30, tft.maxX(), 176, COLOR_BLACK);
  tft.drawText(0, 80, "Pression:    -.- bar       ", COLOR_WHITE);
  tft.drawLine(10, 101, tft.maxX()-10, 101, COLOR_WHITE);
  tft.drawText(0, 110, "                          ", COLOR_WHITE);
  
  }
