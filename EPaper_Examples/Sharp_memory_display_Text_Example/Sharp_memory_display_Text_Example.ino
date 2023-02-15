/*
  Text example for SHARP memory display with Adafruit's Adafruit_SharpMem
  and GFX libraries.

  This example reads the millis() and an analog sensor and displays both.
  It draws the labels in the setup() and updates the canvas with the
  actual values in the loop().
  Uses the following libraries:
  http://librarymanager/All#Adafruit_GFX
  http://librarymanager/All#Adafruit_SharpMem
    and fonts from the GFX library.
   Circuit:
   - SHARP memory display attached to SPI pins listed below

  created 20 Jan 2021
  updated 14 Feb 2023
  by Tom Igoe
*/

// include libraries and fonts:
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
// see https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
// for a list of fonts available in the GFX lib
// or custom fonts from http://oleddisplay.squix.ch/#/home
#include<Fonts/FreeSans12pt7b.h>

// TFT control pins:
const int SHARP_SCK = 13;
const int SHARP_SDI = 11;
const int SHARP_CS = 10;
// change these to match your display's resolution:
const int SHARP_WIDTH = 144;
const int SHARP_HEIGHT = 168;

// initialize the screen:
Adafruit_SharpMem display(SHARP_SCK, SHARP_SDI, SHARP_CS,
                          SHARP_WIDTH, SHARP_HEIGHT);
// set an offscreen buffer for things you want to update frequently:
GFXcanvas1 canvas(60, 60);

int fontColor = 0;  // white
int bgColor = 1;         // black
void setup() {
  // initialize serial and wait for serial monitor to open:
  Serial.begin(9600);
  if (!Serial) delay(3000);
  display.begin();
  display.clearDisplay();
  // set screen rotation (0-3):
  // might need to change depending on which display you use:
  display.setRotation(0);
  Serial.println("Display is good to go");

  // set fonts for both display and canvas:
  display.setFont(&FreeSans12pt7b);
  canvas.setFont(&FreeSans12pt7b);

  // clear the display:
  display.fillScreen(bgColor);
}


void loop() {
  // read the sensor:
  int sensorReading = analogRead(A0);
  display.fillRect(0, 0, display.width(), display.height(), bgColor);
  display.setTextColor(fontColor);
  // move the cursor to 0,30 (because fonts measure from their baseline):
  display.setCursor(0, 30);
  // print label (spaces for consistent columns):
  display.print("secs:   ");
  // print seconds:
  display.println(millis() / 1000);
  // print label:
  display.print("sensor: ");
  // print sensor reading:
  display.println(sensorReading);
  display.refresh();
}
