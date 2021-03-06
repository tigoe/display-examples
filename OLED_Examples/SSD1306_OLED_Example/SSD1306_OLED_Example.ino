/*
  Minimal example for SSD1306 OLED display
  manufacturer's site: http://www.solomon-systech.com/en/product/advanced-display/oled-display-driver-ic/ssd1306/
  datasheet: https://www.crystalfontz.com/controllers/SolomonSystech/SSD1306/339/
  library site: https://github.com/adafruit/Adafruit_SSD1306
    
  These displays are common and inexpensive online, and require only the
  I2C pins (SDA and SCL) from an Arduino. The Adafruit library works well with them.
  If you want custom fonts, check out fonts from http://oleddisplay.squix.ch/#/home

  This example reads the millis() and ana analog sensor and displays both.
  It's written for a 128x64 display, but can be modified to fit a 128x32 display as well.
  Change the SCREEN_HEIGHT to change displays, and adjust font sizes and cursor locations
  to suit your application.

  created 10 Feb 2020
  by Tom Igoe
  based on the Adafruit_SSD1306 library examples
 */
 
#include <Wire.h>
#include <Adafruit_SSD1306.h>
// see https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
// for a list of fonts available in the GFX lib
// or custom fonts from http://oleddisplay.squix.ch/#/home
#include<Fonts/FreeSans9pt7b.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    0  // Reset pin for display (0 or -1 if no reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // initialize serial and wait 3 secs for serial monitor to open:
  Serial.begin(9600);
  if (!Serial) delay(3000);
  // I2C address is 0x3C, or 3D for some 128x64 modules: 
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("Display setup failed");
    while (true);
  }
    // set fonts botforh display:
  display.setFont(&FreeSans9pt7b);
  Serial.println("Display is good to go");
}

void loop() {
  int sensorReading = analogRead(A0);

  /* you get 10 charcters across at this size using the default font
    so make your text accordingly. If you want to try other fonts,
    check out fonts from http://oleddisplay.squix.ch/#/home
  */
  // clear the display:
  display.clearDisplay();
  // set the text size to 1:
  display.setTextSize(1);
  // set the text color to white:
  display.setTextColor(SSD1306_WHITE);
  
  // move the cursor to 0,0:
  display.setCursor(0, 12);
  // print the seconds:
  display.print("secs:");
  display.print(millis() / 1000);
  
  // move the cursor down 20 pixels:
  display.setCursor(0, 30);
  // print a sensor reading:
  display.print("sensor:");
  display.print(sensorReading);
  // push everything out to the screen:
  display.display();
}
