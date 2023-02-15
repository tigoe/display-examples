/*
  Font test  for ePaper display
  Uses Adafruit EPD library: http://librarymanager/All#Adafruit_EPD

  Circuit:
   - 1.54-inch ePaper display connected to SPI pins, and connected to
   the pins listed below.

  created 15 Jan 2021
  updated 14 Feb 2023
  by Tom Igoe
*/

#include "Adafruit_EPD.h"
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include "font.h"

// pin numbers. In addition to these, the SPI pins
// must be connected, and note that EPD_CS is the SPI CS pin:
const int EPD_CS = 10;
const int EPD_DC = 9;
const int SRAM_CS = 8; // for boards without a frame buffer, set to -1
const int EPD_RESET = 5;
const int EPD_BUSY = 7;

/*
  You may need to use a different initializer depending on your screen.
  see
  https://github.com/adafruit/Adafruit_EPD/blob/master/examples/EPDTest/EPDTest.ino
  lines 19ff. for all the chipsets that the Adafruit EPD supports.
*/
// supports Adafruit's 1.54inch displays, Sparkfun's SparkX 1.54" display:
 Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY); 
// Uncomment the following line if you are using 1.54" EPD with  SSD1681
// Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS,EPD_BUSY);

void setup() {
  Serial.begin(9600);
  if (!Serial) delay(3000);
  // start the display:
  display.begin(SPI_MODE3);
  display.clearDisplay();
  // set the text color to black:
  display.setTextColor(EPD_BLACK);
  Serial.println("end of setup");
}

void loop() {
  String now = "12:34:56\n01/20/21";
  Serial.println(now);
  // set large font:
  display.setFont(&FreeSans12pt7b);
  display.clearBuffer();
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(now, 0, 0, &x1, &y1, &w, &h);

  Serial.print(w);
  Serial.print(",");
  Serial.println(h);
  // move the cursor to 0,0:
  display.setCursor(0, 24);
  display.print(now);

  // change font to be smaller
  display.setFont(&FreeSans9pt7b);
  // move the cursor down 20 pixels:
  display.setCursor(0, 80);
  display.print(now);

   // change font to be smaller
  display.setFont(&Open_Sans_Regular_6);
  // move the cursor down 20 pixels:
  display.setCursor(0, 120);
  display.print(now);
  // push everything out to the screen:
  display.display();
  delay(20000);
}
