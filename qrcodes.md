# QR Codes on Microcontroller Displays
[QR Codes](https://www.qrcode.com/en/) are a useful way to transfer text information from one device to another via  browser and camera.  You can use them to transfer URLs, phone numbers, text messages, addresses, or any other textual information. Generally, mobile device QR code readers are context sensitive, and can pick the right app to open a text string of a given format (like a URL). On microcontroller-based devices, they can be a way to transfer identifying information like IP or MAC addresses, Bluetooth LE service UUIDs, or anything else your mobile phone or tablet might need to know about your microcontroller device in order to communicate with it. 

## QR Code Examples
QR codes can be generated from a text string and translated to a microcontroller display using Richard Moore's [qrcode library for Arduino]() and the graphics library for your particular display. This repository contains examples for multiple display types:
* [QRCode example for EPaper displays](https://github.com/tigoe/display-examples/tree/main/EPaper_Examples/EInk_QRCode_Test)
* [QRCode example for ST7735/7789 TFT displays](https://github.com/tigoe/display-examples/tree/main/TFT_Examples/ST7789/ST7789_QR_Example)
* [QRCode example for monochrome OLED displays](https://github.com/tigoe/display-examples/tree/main/OLED_Examples/SSD1306_QRCode_Test)
* [QRCode example for Sparkfun MicroOLED](https://github.com/tigoe/display-examples/tree/main/OLED_Examples/Micro_OLED/Micro_OLED_QRcode_example)

All of these examples follow the same pattern. After initializing the display, print a prompt to the Serial Monitor, then they wait for an incoming serial string and display it. Regardless of which display you use, the main QR-generating code will be more or less the same. The code and comments below indicate how to take text in an Arduino String object and convert it to a QR Code:

````arduino
// before the setup, initialize your libraries and screen's
// I/O pin connections

// in the setup, initialize UART serial communication 
// and the display

// in the main loop, display the QR code:

void displayQrCode(String message) {
  // Create the QR code
  QRCode qrcode;
  int qrVersion = 4;
  int qrErrorLevel = ECC_HIGH;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  // initialize the QR code text:
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset. 
  // Start with an arbitrary offset of 10px:
  int offset = 10;
  // Block size depends on the number of blocks  per side
  // and the display dimensions. qrcode.size gives you
  // the number of blocks in the QR code. Subtract twice the 
  // offset width (arbitrary) from the display's smallest
  // dimension, then divide by the qrcode.size,
  // and you'll have a block size that should make the QR code
  // fit well on the display:
  int blockSize = (display.height() - (offset * 2)) / qrcode.size;
  // fill the screen with the background color:
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
  // if you need to refresh the display (e.g. ePaper displays)
  // do it here, after the nested loops.

  // print the message:
  Serial.println(message);
}
````