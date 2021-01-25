/*
  Text example for ST7789 TFT display with Adafruit's Adafruit_ST7789
  and GFX libraries.

  Shows how to use a canvas from the Adafruit_GFX library
  to update part of a display, avoiding the flicker of a full
  screen update

  This example reads the millis() and an analog sensor and displays both.
  It draws the labels in the setup() and updates the canvas with the
  actual values in the loop().
  Uses the following libraries:
  http://librarymanager/All#Adafruit_GFX
  http://librarymanager/All#Adafruit_ST7789
    and fonts from the GFX library.
   Circuit:
   - ST7789 color display attached to SPI pins
   and TFT pins listed below

  created 20 Jan 2021
  by Tom Igoe
*/

// include libraries and fonts:
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
// see https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
// for a list of fonts available in the GFX lib
// or custom fonts from http://oleddisplay.squix.ch/#/home
#include<Fonts/FreeSans18pt7b.h>

// TFT control pins:
const int TFT_CS = 10;
const int TFT_RST = 9;
const int TFT_DC = 8;
const int TFT_TE = 7;
// change these to match your display's resolution:
const int TFT_WIDTH = 240;
const int TFT_HEIGHT = 240;

Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// set an offscreen buffer for thigns you want to update frequently:
GFXcanvas1 canvas(80, 80);

int fontColor = 0x6677FF;  // light blue
int bgColor = 0x0;         // black
void setup() {
  // initialize serial and wait for serial monitor to open:
  Serial.begin(9600);
  while (!Serial);
  display.init(TFT_WIDTH, TFT_HEIGHT);
  // set screen rotation (0-3):
  // might need to change depending on which display you use:
  display.setRotation(3);
  Serial.println("Display is good to go");
  
  // set fonts for both display and canvas:
  display.setFont(&FreeSans18pt7b);
  canvas.setFont(&FreeSans18pt7b);

  // clear the display:
  display.fillScreen(bgColor);
  // set the text color to teal:
  display.setTextColor(fontColor);
  // move the cursor to 0,30 (because fonts measure from their baseline):
  display.setCursor(0, 30);
  display.println("secs:");
  display.print("sensor:");
}


void loop() {
  // read the sensor:
  int sensorReading = analogRead(A0);
  // clear the canvas with a rect in the background color:
  canvas.fillRect(0, 0, canvas.width(), canvas.height(), bgColor);
  // add a border in the text color so you can see the canvas' bounds:
  canvas.drawRect(0, 0, canvas.width(), canvas.height(), fontColor);
  // move the cursor to 0,30 (because fonts measure from their baseline):
  canvas.setCursor(0, 30);
  // print the seconds:
  canvas.println(millis() / 1000);
  // print a sensor reading:
  canvas.print(sensorReading);
  // update the display with the canvas:
  display.drawBitmap(120, 0, canvas.getBuffer(),
                     canvas.width(), canvas.height(),
                     fontColor, bgColor);
}