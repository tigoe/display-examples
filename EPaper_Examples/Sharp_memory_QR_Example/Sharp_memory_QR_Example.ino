/*
  QR Code generator for SHARP memory display
   Displays a QR code on a SHARP memory display
   Uses Adafruit SharpMem library: http://librarymanager/All#Adafruit_Adafruit_SharpMem
   and Adafruit's GFX library: http://librarymanager/All#Adafruit_SharpMem
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Code is based on qrcode library example and Adafruit_SharpMem example.

   Circuit:
   - SHARP memory display attached to SPI pins listed below

   To test, enter a text string, then scan it with your mobile device

  created 9 Feb 2021
  by Tom Igoe
*/

#include "qrcode.h"
// include libraries:
#include <Adafruit_GFX.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>


// TFT control pins:
const int SHARP_SCK = 13;
const int SHARP_SDI = 11;
const int SHARP_CS = 10;
// change these to match your display's resolution:
const int SHARP_WIDTH = 144;
const int SHARP_HEIGHT = 168;

// colors for a color display:
const int backgroundColor = 0x01; // white
const int foregroundColor = 0x00; // black

// initialize the screen:
Adafruit_SharpMem display(SHARP_SCK, SHARP_SDI, SHARP_CS,
                          SHARP_WIDTH, SHARP_HEIGHT);
void setup() {
  // initialize serial:
  Serial.begin(9600);
  // when reading serial input set a 10ms timeout:
  Serial.setTimeout(10);
  // wait 3 sec. for serial monitor to open:
  while (!Serial) delay(3000);
  // start the display:
  display.begin();
  display.clearDisplay();
  // fill with the background color:
  display.fillScreen(backgroundColor);
  Serial.println("Enter a text message to display:");
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
  // settings will get you about 100 bytes:
  int qrVersion = 4;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_HIGH;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  int offset = 10;
  int blockSize = (display.height() - (offset * 2)) / qrcode.size;
  // fill with the background color:
  display.fillScreen(backgroundColor);

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
      int blockColor = backgroundColor;
      // if the block value is 1, set color to foreground color instead:
      if (blockValue == 1) {
        blockColor = foregroundColor;
      }
      // display the block on the screen:
      display.fillRect(blockX, blockY, blockSize, blockSize, blockColor);
    }
  }
  display.refresh();
  // print the message and display it:
  Serial.println(message);
}
