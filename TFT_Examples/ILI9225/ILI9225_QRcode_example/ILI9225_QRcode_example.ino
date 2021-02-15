/*
  QR Code generator for an ILI9225 TFT Display
   Displays a QR code on a TFT display
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

  created 14 Feb 2021
  by Tom Igoe
*/

#include "SPI.h"
#include "TFT_22_ILI9225.h" // display library
#include "qrcode.h"

// display pins:
#define TFT_RST 9
#define TFT_RS  8
#define TFT_CS  10
#define TFT_LED -1   // -1 if wired to +V directly

// change these to match your display's resolution:
const int TFT_WIDTH = 220;
const int TFT_HEIGHT = 176;

// colors for a color display:
const int backgroundColor = 0xFFFFFF; // white
const int foregroundColor = 0x000000; // black

// initialize the display:
TFT_22_ILI9225 display = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // when reading serial input set a 10ms timeout:
  Serial.setTimeout(10);
  // wait 3 sec. for serial monitor to open:
  if (!Serial) delay(3000);
  // start the display:
  // initialize the display
  display.begin();
  // clear the screen:
  display.clear();
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
  int qrErrorLevel = ECC_MEDIUM;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  int offset = 10;
  int blockSize = (TFT_HEIGHT - (offset * 2)) / qrcode.size;
  // fill with the background color:
  display.setBackgroundColor(backgroundColor);

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
      display.fillRectangle(blockX, blockY,
                            blockX + blockSize, blockY + blockSize,
                            blockColor);
    }
  }
  // display.println("Scan me");
  // print the message and display it:
  Serial.println(message);
}
