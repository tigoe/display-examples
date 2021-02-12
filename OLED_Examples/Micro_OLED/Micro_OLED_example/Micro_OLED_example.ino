/*
  Minimal example for Sparkfun Micro OLED display

  Sparkfun's SSD1306 display doesn't work
  with the Adafruit library, even though they are the same driver.
  The following libraries are used here:
  http://librarymanager/All#Wire
  http://librarymanager/All#SparkFun_Micro_OLED
  The circuit:
  - Sparkfun MicroOLED display connected to SPI pins, and the
    pins listed below.

  This example reads the millis() and an analog sensor and displays both.
  It's written for a 64x48 display, 
 
  created 21 Jan 2021
  modified 12 Feb 2021
  by Tom Igoe
*/
// include libraries:

#include <Wire.h>
#include <SFE_MicroOLED.h>

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 48;

// board pins:
const int OLED_RESET = 9;
const int OLED_DC = 8;

// initialize the library:
MicroOLED display(OLED_RESET, OLED_DC);


void setup() {
  // start the display:
  Wire.begin();
  display.begin(0x3D, Wire);
  // clear all memory:
  display.clear(PAGE);
}

void loop() {
  // read a sensor:
  int sensorReading = analogRead(A0);
  // clear the screen:
  display.clear(PAGE);
  // Set font to smallest, cursor to top-left:
  display.setFontType(0);
  display.setCursor(0, 0);

  // print seconds:
  display.print("secs:");
  display.println(millis() / 1000);
  // print a sensor reading:
  display.print("sensor:");
  display.println(sensorReading);
  // update the display:
  display.display();
}
