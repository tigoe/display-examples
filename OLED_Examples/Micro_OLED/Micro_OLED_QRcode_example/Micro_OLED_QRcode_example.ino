/*
  
  QR Code generator for SSD1306 Display
   Displays a QR code on a SSD1306 64x48 pixel display
   Uses Sparkfun microOLED library http://librarymanager/All#SparkFun_Micro_OLED
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Code is based on qrcode library example.
   
   To test, enter a text string, then scan it with your mobile device

  created 12 Feb 2021
  by Tom Igoe
*/
// include libraries:
#include "qrcode.h"
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
  // initialize serial:
  Serial.begin(9600);
  // when reading serial input set a 10ms timeout:
  Serial.setTimeout(10);
  // wait 3 sec. for serial monitor to open:
  if (!Serial) delay(3000);
  // start the display:
  Wire.begin();
  display.begin(0x3D, Wire);
  // clear memory:
  display.clear(PAGE);
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
  // settings will support a string of about 100 bytes:
  int qrVersion = 4;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_MEDIUM;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display.
  // With a small display like this, blocks are basically 1 pixel x 1 pixel
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  int offset = 1;
  int blockSize = SCREEN_HEIGHT / qrcode.size;
  // clear the display:
  display.clear(PAGE);

  // read the bytes of the QR code and set the blocks light or dark, accordingly:
  // vertical loop:
  for (byte y = 0; y < qrcode.size; y++) {
    // horizontal loop:
    for (byte x = 0; x < qrcode.size; x++) {
      // calculate the block's X and Y positions:
      int blockX = (x * blockSize) + offset;
      int blockY = (y * blockSize) + offset;
      // read the block value from the QRcode:
      int blockValue = qrcode_getModule(&qrcode, x, y);
      // if the block value is 1, set color to foreground color instead:
      if (blockValue == 1) {
        // display the block on the screen:
        display.pixel(blockX, blockY);
      }

    }
  }
  // print the message and display it:
  Serial.println(message);
  display.display();
}
