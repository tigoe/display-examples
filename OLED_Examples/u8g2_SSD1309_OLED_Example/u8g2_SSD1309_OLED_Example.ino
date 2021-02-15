/*
  Minimal example for SS1309 128x64 Transparent OLED display

  This example reads the millis() and an analog sensor and displays both.
  Circuit:
  - SSD1309 128x64 Transparent OLED screen:
  -   https://www.crystalfontz.com/product/cfal12856a00151b-128x56-transparent-oled-screen
  - Crystalfontz OLED breakout board:
  -   https://www.crystalfontz.com/product/cfa10105-oled-breakout-board
  - Breakout board pins connected as below:
    - Breakout pin 1: 3.3V
    - Breakout pin 2: Ground
    - Breakout pin 3: Arduino SPI CLK
    - Breakout pin 4: Arduino SPI SDO
    - Breakout pin 5: Arduino SPI CS (OLED_CS below)
    - Breakout pin 7: Arduino OLED_DC
    - Breakout pin 9: Arduino OLED_RESET

  created 25 Jan 2021
  modified 15 Feb 2021
  by Tom Igoe
*/

#include <U8g2lib.h>
#include <SPI.h>
// set pins.
const int OLED_CS = 10;
const int OLED_DC = 9;
const int  OLED_RESET =  8;

// initialize the display with the right driver. See
// https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#constructor-name
// for driver names. There are many. It goes:
// U8G2_driver_resolution_name_bufferSize_commInterface:
U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI display(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET);


void setup() {
  // initialize serial and display
  Serial.begin(9600);
  display.begin();
  // rotation values are at
  // https://github.com/olikraus/u8g2/wiki/u8g2reference#setdisplayrotation
  // not really needed, as it's set in the initialization, but here for reference:
  display.setDisplayRotation(U8G2_R0);
  // light fonts:
  display.setFontMode(1);
  // dark display:
  display.setDrawColor(1);
}

void loop() {
  int sensorReading = analogRead(A0);

  // clear the display:
  display.clearBuffer();
  // fonts are found at https://github.com/olikraus/u8g2/wiki/fntlistall#u8g2-font-names
  display.setFont(u8g2_font_crox4h_tf);

  // move the cursor to 0,0:
  display.setCursor(0, 20);
  // print the seconds:
  display.print("secs:");
  display.print(millis() / 1000);

  // move the cursor down 20 pixels:
  display.setCursor(0, 40);
  // print a sensor reading:
  display.print("sensor:");
  display.print(sensorReading);
  // push everything out to the screen:
  display.sendBuffer();
}
