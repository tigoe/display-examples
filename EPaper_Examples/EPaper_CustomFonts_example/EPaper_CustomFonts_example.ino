/*
  Minimal example for SSD1306 OLED display with custom fonts
  Uses Adafruit EPD library: http://librarymanager/All#Adafruit_EPD

  Circuit:
   - 1.54-inch ePaper display connected to SPI pins, and connected to
   the pins listed below.

  If you want to try other fonts, check out fonts from http://oleddisplay.squix.ch/#/home

  created 15 Jan 2021
  updated 14 Feb 2023
  by Tom Igoe
*/
#include "Adafruit_EPD.h"
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
  see https://github.com/adafruit/Adafruit_EPD/blob/master/examples/EPDTest/EPDTest.ino
  lines 19ff. for all the chipsets that the Adafruit EPD supports.
*/
// supports Adafruit's 1.54inch displays, Sparkfun's SparkX 1.54" display:
Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// supports WaveShare's 1.54" display. Set SRAM_CS to -1:
//Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//Uncomment the following line if you are using 2.13" EPD with IL0373
// Adafruit_IL0373 display(212, 104, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//#define FLEXIBLE_213


// 20 second update rate
int interval = 20000;
long lastUpdate = 0;

void setup() {
  // start the display:
  display.begin();
  display.clearBuffer();
  display.setFont(&Open_Sans_Regular_12);
    #if defined(FLEXIBLE_213) || defined(FLEXIBLE_290)
  // The flexible displays have different buffers and invert settings!
  display.setBlackBuffer(1, false);
  display.setColorBuffer(1, false);
#endif
  display.display();
}

void loop() {
  if (millis() - lastUpdate > interval) {
    int sensorReading = analogRead(A0);
    // clear the display:
    display.clearDisplay();
    // set the text size to 2:
    display.setTextSize(2);
    // set the text color to black:
    display.setTextColor(EPD_BLACK);

    // move the cursor to 0,0:
    display.setCursor(0, 0);
    // print the seconds:
    display.print("secs:");
    display.print(millis() / 1000);

    // move the cursor down 20 pixels:
    display.setCursor(0, 20);
    // print a sensor reading:
    display.print("sensor:");
    display.print(sensorReading);
    // push everything out to the screen:
    display.display();
  }
}
