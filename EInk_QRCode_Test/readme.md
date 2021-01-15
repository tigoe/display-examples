# EInk and QR Code Example 
This example Displays a QR code on an eInk display. It uses Uses [Adafruit EPD library](https://github.com/adafruit/Adafruit_EPD) and Richard Moore's [qrcode library](https://github.com/ricmoo/QRCode) to generate a QR Code on a 1.54" EInk display using a text string entered via the Serial Monitor. 

It was tested on an Arduino Nano 33 IoT and a Nano Every using a (now discontinued) SparkX 1.54" 3-color EInk breakout board. Presumably it will work with any similar breakout board, though I have yet to test. 

## Pin Connections
The pins of the display are connected as follows:
* DCS - Arduino pin 10. This is the SPI CS pin
* D/C - Arduino pin 9.
* SRCS -  Arduino pin 8
* RESET - Arduino pin 7
* BUSY- Arduino pin 6. This is optional. If you don't use it, set this to -1.
* The SPI pins also need to be connected to the EInk display as well.

## Notes
eInk displays are slow to update, and aren't meant to be used as animated displays, but the advantage they have over other displays is that they retain their latest image when powered off. This makes them really useful for displaying information like a device's IP address, or a URL for its control page. 

The [qrcode library](https://github.com/ricmoo/QRCode) generates a large byte array that contains the QRcode data. It encodes the two-dimensional data as a one-dimensional array. so you need to iterate over it in two nested for loops, one for X and one for Y. If a given block is filled in, the corresponding value of the byte is 1; otherwise it's 0. The library isn't written for any display, so you can use whatever display you want.

The QRCode version and error correction determine the maximum number of bytes that your message can contain, and it's not a straightforward formula. There is a [frequently-quoted table](https://github.com/ricmoo/QRCode#data-capacities) from [Denso](https://www.qrcode.com/), the maker of QR Codes, that shows the capacity depending on the QRCode version and error correction you choose. Denso [explains it further](https://www.qrcode.com/en/about/version.html) on their site. [Project Nayuki](https://www.nayuki.io/page/creating-a-qr-code-step-by-step), which Richard Moore gives credit to, is also good for explaining it. My rule of thumb was that a version 4 QRCode was good for about 100 bytes of alphanumeric text, and fits most well-formed URLs nicely. 

The [Adafruit EPD library](https://github.com/adafruit/Adafruit_EPD) is written with their EPaper boards in mind, but seems to work with other eInk boards as well. I plan to test with whatever ones I have. Their [explainer page](https://learn.adafruit.com/adafruit-eink-display-breakouts?view=all) is helpful for getting started with eInk displays.


