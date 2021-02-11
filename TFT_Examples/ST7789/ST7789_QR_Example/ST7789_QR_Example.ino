/*
  QR Code generator for an ST77735 or ST7789 TFT Display
   Displays a QR code on a TFT display
   Uses Adafruit ST7735/ST7789 library: http://librarymanager/All#Adafruit_Adafruit_ST7735
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Code is based on qrcode library example and Adafruit_ST7789 example.
   Circuit:
   - 1.54-inch (min) TFT display connected to SPI pins, and connected to
   the pins listed below.
   - Screen SDI <-> microcontroller SPI SDO
   - Screen SCK <-> microcontroller SPI SCK
   - Screen CS <-> microcontroller SPI CS
   - Screen D/C <-> microcontroller digital output pin
   Your pin numbers may vary depending on your display. See
   the Adafruit ST7735/7789 library examples for different initializers.

   To test, enter a text string, then scan it with your mobile device

  created 8 Jan 2021
  modified 11 Feb 2021
  by Tom Igoe
*/

#include "qrcode.h"
// include libraries:
#include <Adafruit_GFX.h>
//#include <Adafruit_ST7735.h> //  for ST7735 displays
#include <Adafruit_ST7789.h>   //  for ST7789 displays
#include <SPI.h>

// TFT control pins:
// for any display that doesn't have a given pin, set that 
// pin to -1. For example, the MakerFocus 1.3" ST7789 screen has 
// no CS pin. In that case, set TFT_CS to -1.
const int TFT_CS =  10;
const int TFT_RST = 9;
const int TFT_DC = 8;

// change these to match your display's resolution:
const int TFT_WIDTH = 240;
const int TFT_HEIGHT = 240;

// colors for a color display:
const int backgroundColor = 0xFFFFFF; // white
const int foregroundColor = 0x000000; // black

/*
  Initialize the display library instance.
  You may need to use a different initializer depending on your screen. See
  https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/examples/displayOnOffTest/displayOnOffTest.ino
  lines 45ff. for all the displays that the Adafruit library supports.
*/
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
//Adafruit_ST7735 display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // when reading serial input set a 10ms timeout:
  Serial.setTimeout(10);
  // wait 3 sec. for serial monitor to open:
  while (!Serial) delay(3000);
  // start the display:
  display.init(TFT_WIDTH, TFT_HEIGHT);
  // For the MakerFocus 1.3" module with no CS pin,
  // you need to change the SPI mode:
  //  display.init(TFT_WIDTH, TFT_HEIGHT, SPI_MODE3);
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
  // print the message and display it:
  Serial.println(message);
}
