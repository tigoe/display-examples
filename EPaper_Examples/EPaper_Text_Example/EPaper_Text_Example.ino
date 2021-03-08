/*
  Minimal example for ePaper display
  Uses Adafruit EPD library: http://librarymanager/All#Adafruit_EPD

  Circuit:
   - 1.54-inch ePaper display connected to SPI pins, and connected to
   the pins listed below.

  created 15 Jan 2021
  by Tom Igoe
*/

#include "Adafruit_EPD.h"

// pin numbers. In addition to these, the SPI pins
// must be connected, and note that EPD_CS is the SPI CS pin:
const int EPD_CS = 10;
const int  EPD_DC = 9;
const int  SRAM_CS = -1; //8;  // for boards without a frame buffer, set to -1
const int  EPD_RESET = 7;
const int EPD_BUSY = 6;

/*
  You may need to use a different initializer depending on your screen.
  see https://github.com/adafruit/Adafruit_EPD/blob/master/examples/EPDTest/EPDTest.ino
  lines 19ff. for all the chipsets that the Adafruit EPD supports.
*/
// supports Adafruit's 1.54inch displays, Sparkfun's SparkX 1.54" display:
//Adafruit_IL0373 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// supports WaveShare's 1.54" display. Set SRAM_CS to -1:
Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// 20 second update rate
int interval = 20000;
long lastUpdate = 0;

void setup() {
  Serial.begin(9600);
  // start the display:
  display.begin();
  display.clearBuffer();
  display.display();
}

void loop() {
  if (millis() - lastUpdate > interval) {
    int sensorReading = analogRead(A0);
    Serial.println(millis() / 1000);
    // clear the display:
    display.clearDisplay();
    // set the text size to 2:
    display.setTextSize(2);
    // set the text color to black:
    display.setTextColor(EPD_BLACK);

    // move the cursor to 0,0:
    display.setCursor(0, 20);
    // print the seconds:
    display.print("secs:");
    display.print(millis() / 1000);

    // move the cursor down 20 pixels:
    display.setCursor(0, 0);
    // print a sensor reading:
    display.print("sensor:");
    display.print(sensorReading);
    // push everything out to the screen:
    display.display();
    lastUpdate = millis();
  }
}
