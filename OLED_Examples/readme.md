# OLED Displays

## Hardware 

### SSD1306
The Solomon Systech SSD1306 OLED driver IC is a popular and inexpensive display driver in lots of display breakouts. You can find them on most of the popular electronics sites: [Adafruit](https://www.adafruit.com/product/661), [Sparkfun](https://www.sparkfun.com/products/17153) (including their [MicroOLED breakout](https://www.sparkfun.com/products/13003)), [DFRobot](https://www.dfrobot.com/product-1576.html), [Crystalfontz](https://www.crystalfontz.com/search.php?q=ssd1306&submit=Search), [MakerFocus](https://www.makerfocus.com/collections/oled), [Amazon](https://smile.amazon.com/s?k=ssd1306+oled+display), and many others. The displays are small, inexpensive and easy to use, and useful for simple displays. There are a number of variants from Solomon Systech, which you'll encounter in various vendors' products.

This driver chip has both an SPI and an I2C interface, though many of the less expensive models break out only the I2C pins. This is convenient for saving other pins for other I/O purposes.

### Other OLED Displays
Sparkfun's [Micro OLED](https://www.sparkfun.com/products/13003) is a tiny display, just 64x48 pixels. The [Micro OLED Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/micro-oled-breakout-hookup-guide) is useful if you are using this board. It works best with their [Micro OLED library](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/tree/V_1.0.0).

### Crystalfontz Displays
Crystalfontz makes a number of displays, and I've just started to work with a few of them. These notes are very preliminary. 
* [128x128 Round OLED display](https://www.crystalfontz.com/product/cfal128128b0011w-128x128-round-oled-display) - uses SSD1327 driver
* [128x56 Transparent OLED Display](https://www.crystalfontz.com/product/cfal12856a00151b-128x56-transparent-oled-screen) - uses  SSD1309 driver. Works with u8g2 library and OLED breakout board below. 
* [OLED Breakout Board](https://www.crystalfontz.com/product/cfa10105-oled-breakout-board). Works with some of Crystalfontz' displays, but not the round ones. 

### Pin Connections
See the [SPI connections](../readme.md#spi-connections) section of the main page of this repository for a list of typical pin connections. 

## Libraries
Despite having the same driver, not all of these displays interoprate with all libraries. [Adafruit's SSD1306 library](https://github.com/adafruit/Adafruit_SSD1306) works well with all the 128x64 and 128x32 displays that I've tried, but not with ones that have other resolutions, like the Sparkfun Micro OLED, which has a 64x48 resolution. 

The [u8g2 library](https://github.com/olikraus/u8g2/wiki) by Oli Kraus, is intended as a universal monochrome display library for OLED, eInk, TFT, and other displays. It supports some SSD130x boards, but not all. 

## Examples
* [SSD1306 Text example](SSD1306_OLED_Example)
* [SSD1306 QRCode example](SSD1306_QRCode_Test). This is written for the 128x64 models. It's possible to make smaller QR codes on the 128x32 models, with some changes, noted in the comments.
* [SSD1306 OLED example with custom fonts](SSD1306_OLED_Example_CustomFonts) from squix.ch


