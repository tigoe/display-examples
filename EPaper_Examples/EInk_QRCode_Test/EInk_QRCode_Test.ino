
/*
  QR Code generator for eInk Display
   Displays a QR code on an eInk display
   Uses Adafruit EPD library: http://librarymanager/All#Adafruit_EPD
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Code is based on qrcode library example and Adafruit_EPD example.
   To test, enter a text string, then scan it with your mobile device.
   Circuit:
   - 1.54-inch ePaper display connected to SPI pins, and connected to
   the pins listed below.
   - Screen SDI <-> microcontroller SPI SDO
   - Screen SCK <-> microcontroller SPI SCK
   - Screen CS <-> microcontroller SPI CS

  created 8 Jan 2021
  modified 6 Feb 2021
  by Tom Igoe
*/

#include "Adafruit_EPD.h"
#include "qrcode.h"

// pin numbers. Note that EPD_CS is the SPI CS pin:
const int EPD_CS = 10;
const int  EPD_DC = 9;
const int  SRAM_CS = -1;  // for boards without a frame buffer, set to -1
const int  EPD_RESET = 7;
const int EPD_BUSY = 6;
// colors for a monochrome display (Color (red or yellow) is 0x02):
const int foregroundColor = 0x01;  // white
const int backgroundColor = 0x00;  // black

/*
  Initialize the display library instance.
  You may need to use a different initializer depending on your screen.
  see https://github.com/adafruit/Adafruit_EPD/blob/master/examples/EPDTest/EPDTest.ino
  lines 19ff. for all the chipsets that the Adafruit EPD supports.
*/
// supports Adafruit's 1.54inch displays, Sparkfun's SparkX 1.54" display:
Adafruit_IL0373 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// supports WaveShare's 1.54" display. Set SRAM_CS to -1:
//Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // when reading serial input set a 10ms timeout:
  Serial.setTimeout(10);
  // wait 3 sec. for serial monitor to open:
  while (!Serial) delay(3000);
  // start the display:
  display.begin();
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
  int qrVersion = 4;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_LOW;

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
  // print the message and display it:
  Serial.println(message);
  display.display();
}
