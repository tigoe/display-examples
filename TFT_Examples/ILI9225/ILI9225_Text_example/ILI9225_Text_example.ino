
/*

  Text example for IPI9225 TFT display.

  This example reads the millis() and an analog sensor and displays both.
  It draws the labels in the setup() and updates the canvas with the
  actual values in the loop().
   Uses Nkawu's  TFT_22_ILI9225: http://librarymanager/All#TFT_22_ILI9225
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Circuit:
   - TFT display connected to the pins listed below.
   - Screen SDI <-> microcontroller SPI SDO
   - Screen SCK <-> microcontroller SPI SCK
   - Screen CS <-> microcontroller SPI CS
   - Screen RS <-> microcontroller TFT_RS output pin
   - Screen Reset <-> microcontroller TFT_RST output pin

   To test, enter a text string, then scan it with your mobile device

  created 15 Feb 2021
  by Tom Igoe
*/

#include "SPI.h"
#include "TFT_22_ILI9225.h" // display library
#include <../fonts/FreeSans18pt7b.h>


// display pins:
#define TFT_RST 9
#define TFT_RS  8
#define TFT_CS  10
#define TFT_LED -1   // -1 if wired to +V directly

// change these to match your display's resolution:
const int TFT_WIDTH = 220;
const int TFT_HEIGHT = 176;

// colors for a color display:
int fontColor = 0x6677FF;  // light blue
int bgColor = 0x0;         // black

// width needed for the text labels using current font:
int textWidth = 125;
// height needed for a text string using the current font:
int textHeight = 30;

// initialize the display:
TFT_22_ILI9225 display = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // wait 3 sec. for serial monitor to open:
  if (!Serial) delay(3000);
  // start the display:
  // initialize the display
  display.begin();
  // clear the screen:
  display.clear();
  //  orientation orientation:
  // 0=portrait,
  // 1=right rotated landscape,
  // 2=reverse portrait,
  // 3=left rotated landscape
  display.setOrientation(3);
  // fill with the background color:
  display.setBackgroundColor(bgColor);

  // set fonts
  display.setGFXFont(&FreeSans18pt7b);
  // move the cursor to 0,30 (because fonts measure from their baseline):
  display.drawGFXText(0, textHeight, "secs:", fontColor);
  // move the cursor down another 30 for the next line:
  display.drawGFXText(0, textHeight * 2, "sensor:", fontColor);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A0);
  // display flickers too much if you change it every loop.
  // Do it once a second instead:
  if (millis() % 1000 < 3) {
    // fill the space where the readings go
    // with a rect in the background color:
    display.fillRectangle(textWidth, 0, textWidth * 2, textHeight * 2, bgColor);
    // print the seconds:
    display.drawGFXText(textWidth, textHeight,
                        String(millis() / 1000), fontColor);
    // print a sensor reading:
    display.drawGFXText(textWidth, textHeight * 2,
                        String(sensorReading), fontColor);
  }
}
