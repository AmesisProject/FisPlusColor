/*
    __ ___ ___     _
  | __|_ _| __|  _| |_
  | _| | |\__ \ |_   _|
  |_| |___|___/   |_|

*/

// 2" TFT ILI9229 176X220

/*
   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/

*/

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include "bitmap.h"

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 16  // MOSI
#define TFT_CLK 15   // SCK
#define TFT_LED 0   // 0 if wired to +5V directly

//---------------------------------------------------------------------------------------

#define up 3
#define down 2

//---------------------------------------------------------------------------------------

const int menuSize = 5;
String menuItems[menuSize];

bool upLastState = HIGH;
bool downLastState = HIGH;

int currentMenu = 0;
String temp;
char currentPrintOut[10];

//---------------------------------------------------------------------------------------

#define TFT_BRIGHTNESS 100 // Initial brightness of TFT backlight (optional)

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);

// Variables and constants
uint16_t x, y;
boolean flag = false;



//---------------------------------------------------------------------------------------


/*
   ___ ___ _____ _   _ ___
  / __| __|_   _| | | | _ \
  \__ \ _|  | | | |_| |  _/
  |___/___| |_|  \___/|_|

*/

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.setOrientation(3);

  SplashScreen();

  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);

  menuItems[0] = "TEMP  ";
  menuItems[1] = "TURBO ";
  menuItems[2] = "AFR   ";
  menuItems[3] = "TRIP  ";
  menuItems[4] = "MAP   ";
  

  MenuChanged();

}

/*
   __  __   _   ___ _  _   _    ___   ___  ___
  |  \/  | /_\ |_ _| \| | | |  / _ \ / _ \| _ \
  | |\/| |/ _ \ | || .` | | |_| (_) | (_) |  _/
  |_|  |_/_/ \_\___|_|\_| |____\___/ \___/|_|

*/

void loop() {
  if (digitalRead(up) != upLastState) {
    upLastState = !upLastState;

    if (!upLastState) {
      //Just pressed.
      if (currentMenu > 0) {
        currentMenu--;
      } else {
        currentMenu = menuSize - 1;
      }
      //Serial.println(menuItems[currentMenu]);
      MenuChanged();
    } else {
      //Just released.
    }
  }

  if (digitalRead(down) != downLastState) {
    downLastState = !downLastState;

    if (downLastState) {
      //Just pressed.
      if (currentMenu < menuSize - 1) {
        currentMenu++;
      } else {
        currentMenu = 0;
      }
      MenuChanged();
    } else {
      //Just released
    }

  }
  delay(50);
}

/*
    __ _   _ _  _  ___ _____ ___ ___  _  _ ___
  | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
  |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/

*/

//--------------------------------------------- Page Selection --------------------------------------------------------

void MenuChanged() {
  //tft.clear();
  tft.setFont(Terminal12x16);

  temp = String(menuItems[currentMenu]);
  temp.toCharArray(currentPrintOut, 7);


  tft.drawText(2, 7, currentPrintOut);
  tft.drawLine(0, 1, tft.maxX(), 1, COLOR_BLUE);
  tft.drawLine(0, 26, tft.maxX(), 26, COLOR_BLUE);

  if (currentMenu == 0) {
    Display_1();
  }
  else if (currentMenu == 1) {
    Display_2();
  }

  else if (currentMenu == 2) {
    Display_3();
  }

  else if (currentMenu == 3) {
    Display_4();
  }

  else if (currentMenu == 4) {
    Display_5();
  }


}

//--------------------------------------------- Splash Screen --------------------------------------------------------

void SplashScreen() {
  tft.drawCircle(110, 65, 41, COLOR_WHITE);
  tft.fillCircle(110, 65, 40, COLOR_BLUE);
  tft.drawBitmap(77, 31, VW, 68, 68, COLOR_WHITE);
  tft.setFont(Terminal12x16);
  tft.drawText(50, 120, "VOLKSWAGEN", COLOR_WHITE);
  delay(1000);
  tft.setFont(Terminal12x16);
  tft.drawText(90, 140, "FIS+", COLOR_WHITE);
  delay(3000);
  tft.clear();
  tft.setFont(Terminal12x16);
  tft.drawText(100, 70, "FDR", COLOR_WHITE);
  delay(500);
  tft.drawText(60, 90, "Motorsport", COLOR_WHITE);
  delay(1000);
  tft.clear();
}






/*
  tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
  tft.setFont(Terminal6x8);
  tft.drawText(10, 10, "hello!");
  delay(1000);

  tft.clear();
  tft.drawText(10, 20, "clear");
  delay(1000);

  tft.drawText(10, 30, "text small");
  tft.setBackgroundColor(COLOR_YELLOW);
  tft.setFont(Terminal12x16);
  tft.drawText(90, 30, "BIG", COLOR_RED);
  tft.setBackgroundColor(COLOR_BLACK);
  tft.setFont(Terminal6x8);
  delay(1000);

  tft.drawText(10, 40, "setBacklight off");
  delay(500);
  tft.setBacklight(LOW);
  delay(500);
  tft.setBacklight(HIGH);
  tft.drawText(10, 50, "setBacklight on");
  delay(1000);

  tft.drawRectangle(10, 10, 110, 110, COLOR_BLUE);
  tft.drawText(10, 60, "rectangle");
  delay(1000);

  tft.fillRectangle(20, 20, 120, 120, COLOR_RED);
  tft.drawText(10, 70, "solidRectangle");
  delay(1000);

  tft.drawCircle(80, 80, 50, COLOR_YELLOW);
  tft.drawText(10, 80, "circle");
  delay(1000);

  tft.fillCircle(90, 90, 30, COLOR_GREEN);
  tft.drawText(10, 90, "solidCircle");
  delay(1000);

  tft.drawLine(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_CYAN);
  tft.drawText(10, 100, "line");
  delay(1000);

  for (uint8_t i = 0; i < 127; i++)
    tft.drawPixel(random(tft.maxX()), random(tft.maxY()), random(0xffff));
  tft.drawText(10, 110, "point");
  delay(1000);

  for (uint8_t i = 0; i < 4; i++) {
    tft.clear();
    tft.setOrientation(i);
    tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
    tft.drawText(10, 10, "setOrientation (" + String("0123").substring(i, i + 1) + ")");
    tft.drawRectangle(10, 20, 50, 60, COLOR_GREEN);
    tft.drawCircle(70, 80, 10, COLOR_BLUE);
    tft.drawLine(30, 40, 70, 80, COLOR_YELLOW);
    delay(1000);
  }

  tft.setOrientation(0);
  tft.clear();
  tft.drawText(10, 100, "drawing bitmap");
  delay(1000);
  tft.clear();
  tft.setBackgroundColor(COLOR_BLACK);
  tft.drawBitmap(0, 0, VW, 180, 220, COLOR_WHITE);
  delay(5000);

  tft.setOrientation(0);
  tft.clear();
  tft.setFont(Terminal12x16);
  tft.setBackgroundColor(COLOR_YELLOW);
  tft.drawText(10, 40, "bye!", COLOR_RED);
  tft.setBackgroundColor(COLOR_BLACK);
  tft.setFont(Terminal6x8);
  delay(1000);

  tft.drawText(10, 60, "off");
  delay(1000);

  tft.setBacklight(false);
  tft.setDisplay(false);

  while (true);
*/
