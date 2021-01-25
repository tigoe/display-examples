# OLED Displays

The SSD1306 OLED driver IC is a popular and inexpensive display driver in lots of display breakouts. You can find them on most of the popular electronics sites: [Adafruit](https://www.adafruit.com/product/661), [Sparkfun](https://www.sparkfun.com/products/17153) (including their [MicroOLED breakout](https://www.sparkfun.com/products/13003)), [DFRobot](https://www.dfrobot.com/product-1576.html), [Crystalfontz](https://www.crystalfontz.com/search.php?q=ssd1306&submit=Search), [MakerFocus](https://www.makerfocus.com/collections/oled), [Amazon](https://smile.amazon.com/s?k=ssd1306+oled+display), and many others. The displays are small, inexpensive and easy to use, and useful for simple displays. 

This chip has both an SPI and an I2C interface, though many of the less expensive models break out only the I2C pins. This is convenient for saving other pins for other I/O purposes.

## Libraries
Despite having the same driver, not all of these displays interoprate with all libraries. [Adafruit's SSD1306 library](https://github.com/adafruit/Adafruit_SSD1306) works well with all the 128x64 and 128x32 displays that I've tried, but not with ones that have other resolutions, like the Sparkfun Micro OLED library (though it is possible to modify the Adafruit library to drive that board). One of the advantages of the Adafruit library is that[ Squix.ch's custom font generator](http://oleddisplay.squix.ch/#/home) works well with it. 

Sparkfun [Micro OLED Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/micro-oled-breakout-hookup-guide)
