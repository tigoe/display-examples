/*
  QR Code generator for SSD1306 Display
   Displays a QR code on a SSD1306 128x64 pixel display
   Uses Adafruit EPD library: http://librarymanager/All#Adafruit_SSD1306
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Code is based on qrcode library example and Adafruit_SSD1306 example.
   Circuit:
   - 128x64 SSD1306 OLED display connected to I2C pins.

   This will work with a 128x32 OLED display as long as the
   offset is 1 and the QR version type is <=3.

   To test, enter a text string, then scan it with your mobile device

  created 8 Jan 2021
  modified 6 Feb 2021
  by Tom Igoe
*/

#include "qrcode.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 32; // OLED display height, in pixels
const int OLED_RESET = 0; // Reset pin for display (0 or -1 if no reset pin)
// colors for a monochrome display:
const int foregroundColor = 0x01;  // white
const int backgroundColor = 0x00;  // black

// initialize the display library instance:
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // when reading serial input set a 10ms timeout:
  Serial.setTimeout(10);
  // wait 3 sec. for serial monitor to open:
  if (!Serial) delay(3000);
  // start the display:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // fill with the background color:
  display.fillScreen(backgroundColor);
  // update the display:
  display.display();
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
  int qrVersion = 3;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_HIGH;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  int offset = 1;
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
  // print the message and display it:
  Serial.println(message);
  display.display();
}
