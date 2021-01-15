
/*
  QR Code generator for eInk Display
   Displays a QR code on an eInk display
   Uses Adafruit EPD library: http://librarymanager/All#Adafruit_EPD
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Code is based on qrcode library example and Adafruit_EPD example.

   To test, enter a text string, then scan it with your mobile device

  created 8 Jan 2021
  by Tom Igoe
*/

#include "Adafruit_EPD.h"
#include "qrcode.h"

// pin numbers. In addition to these, the SPI pins
// must be connected, and note that EPD_CS is the SPI CS pin:
const int EPD_CS = 10;
const int  EPD_DC = 9;
const int  SRAM_CS = 8;
const int  EPD_RESET = 7;
const int EPD_BUSY = 6; // optional. for faster response, attach this to a pin

// You may need to use a different initializer depending on your screen.
// This works for 1.54 inch x 1.54 inch displays:
Adafruit_IL0373 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//Adafruit_SSD1680 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//Adafruit_UC8151D display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//Adafruit_IL0373 display(296, 128, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//#define FLEXIBLE_290

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  while(!Serial);
  // start the display:
  display.begin();
  display.clearBuffer();
  display.display();

  // wait for serial monitor to open:
  while (!Serial);
  Serial.println("Enter a text message to display:");
}

void loop() {
  // if there's nothing in the serial buffer, skip the rest of the loop:
  if (!Serial.available()) return;

  // otherwise, read the serial input and make a QR Code:
  String message = Serial.readString();
  Serial.print("Message length: ");
  Serial.println(message.length());

  // Create the QR code
  QRCode qrcode;
  // See table at https://github.com/ricmoo/QRCode
  // or https://www.qrcode.com/en/about/version.html for
  // calculation of data capacity of a QR code. Current
  // settings will get you about 100 bytes:
  int qrVersion = 4;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_LOW;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of empty space around it, hence the offset:
  int offset = 10;
  int blockSize = (display.height() - (offset * 2)) / qrcode.size;

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
      // set the default block color:
      int blockColor = EPD_WHITE;
      // if the block value is 1, set color to white:
      if (blockValue == 1) {
        blockColor = EPD_BLACK;
      }
      // display the block on the screen:
      display.fillRect(blockX, blockY, blockSize, blockSize, blockColor);
    }
  }
  // print the message and display it:
  Serial.println(message);
  display.display();
}
