/*
 QR Code generator for SS1309 128x64 Transparent OLED display
   Displays a QR code on a SSD1309 128x64 pixel display
   Uses u8g2 library: http://librarymanager/All#U8g2lib
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
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

   To test, enter a text string, then scan it with your mobile device

  created 15 Feb 2021
  by Tom Igoe
*/
#include "qrcode.h"
#include <U8g2lib.h>
#include <SPI.h>
// set pins.
const int OLED_CS = 10;
const int OLED_DC = 9;
const int  OLED_RESET =  8;
const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels

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
  // if there's a string in the serial buffer, display it.
  // Then prompt for a message skip the rest of the loop:
  if (Serial.available()) {
    // otherwise, read the serial input and make a QR Code:
    String incoming = Serial.readString();
    displayQrCode(incoming);
    Serial.println("Enter a text message to display:");
  }
}


void displayQrCode(String message) {
  Serial.print("Message length: ");
  Serial.println(message.length());

  // Create the QR code
  QRCode qrcode;
  // See table at https://github.com/ricmoo/QRCode
  // or https://www.qrcode.com/en/about/version.html for
  // calculation of data capacity of a QR code. Current
  // settings will support a string of about 100 bytes:
  int qrVersion = 3;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_HIGH;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  int offset = 1;
  int blockSize = (SCREEN_HEIGHT - (offset * 2)) / qrcode.size;
  // clear the display:
  display.clearBuffer();

  // read the bytes of the QR code and set the blocks light or dark, accordingly:
  // vertical loop:
  for (byte y = 0; y < qrcode.size; y++) {
    // horizontal loop:
    for (byte x = 0; x < qrcode.size; x++) {
      // caculate the block's X and Y positions:
      int blockX = (x * blockSize) + offset;
      int blockY = (y * blockSize) + offset;
      // read the block value from the QRcode:
      int blockValue = qrcode_getModule(&qrcode, x, y);
      // if the block value is 1, draw a block:
      if (blockValue == 1) {
        // display the block on the screen:
        display.drawBox(blockX, blockY, blockSize, blockSize);
      }

    }
  }
  // print the message and display it:
  Serial.println(message);
  // push everything out to the screen:
  display.sendBuffer();
}
