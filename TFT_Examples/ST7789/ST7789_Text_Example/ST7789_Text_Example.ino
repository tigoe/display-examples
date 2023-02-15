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
   - TFT display connected to SPI pins, and connected to
   the pins listed below.
   - Screen SDI <-> microcontroller SPI SDO
   - Screen SCK <-> microcontroller SPI SCK
   - Screen CS <-> microcontroller SPI CS
   - Screen D/C <-> microcontroller digital output pin
   - Screen Reset <-> microcontroller TFT_RST output pin

  Your pin numbers may vary depending on your display. See
   the Adafruit ST7735/7789 library examples for different initializers.

  created 20 Jan 2021
  modified 14 Feb 2023
  by Tom Igoe
*/

// include libraries and fonts:
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
// see https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
// for a list of fonts available in the GFX lib
// or custom fonts from http://oleddisplay.squix.ch/#/home
#include<Fonts/FreeSans18pt7b.h>

// TFT control pins:
// for any display that doesn't have a given pin, set that
// pin to -1. For example, the MakerFocus 1.3" ST7789 screen has
// no CS pin. In that case, set TFT_CS to -1.
const int TFT_CS =  -1;//10;
const int TFT_RST = 9;
const int TFT_DC = 8;

// change these to match your display's resolution:
const int TFT_WIDTH = 240;
const int TFT_HEIGHT = 240;

Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// set an offscreen buffer for things you want to update frequently.
// Size it to the max area you need for the thing to be updated:
GFXcanvas1 canvas(80, 80);

int fontColor = 0x6677FF;  // light blue
int bgColor = 0x0;         // black
void setup() {
  // initialize serial and wait 3 secs for serial monitor to open:
  Serial.begin(9600);
  if (!Serial) delay(3000);
  //display.init(TFT_WIDTH, TFT_HEIGHT);
  // For the MakerFocus 1.3" module with no CS pin,
  // you need to change the SPI mode:
    display.init(TFT_WIDTH, TFT_HEIGHT, SPI_MODE3);
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
