# TFT LCD Displays

There are a few common TFT display drivers on the electronics hobbyist market, and a handful of libraries that work with them. 

## I/O Pins
Most TFT displays tend to have an SPI interface, with some extra pins, as explained on the [main page](../readme.md#spi-connections) of this repo.

## Sitronix ST7735 and ST7789 TFT Displays
All of the displays listed below have been tested with the Adafruit_ST7735/ST7789 libraries and the Adafruit_GFX library, with the modifications mentioned below.
  * Adafruit [1.8" ST7735R display with MicroSD Breakout](https://www.adafruit.com/product/358)
  * Adafruit [1.44" ST7735R display with MicroSD Breakout](https://www.adafruit.com/product/2088)
  * Adafruit [1.54" ST7789 Display with MicroSD](https://www.adafruit.com/product/3787)
  * Adafruit [1.14" Display with MicroSD](https://www.adafruit.com/product/4383)
  * MakerFocus [1.3" LCD Display, no MicroSD](https://bit.ly/3qDYMLo), [Amazon link](https://smile.amazon.com/gp/product/B07P9X3L7M) - This display does not have a CS pin, so it can't be used with other SPI devices at the same time. It works with the Adafruit_ST7789 library, but you have to change the `init()` function to include the SPI mode like so:
  `display.init(width, height, SPI_MODE3);`. 
* DFRobot 7687S [round display](https://www.dfrobot.com/product-1794.html)
  * [DFRobot library for this display](https://github.com/DFRobot/DFRobot_ST7687S)
  * [DFRobot Display library](https://github.com/DFRobot/DFRobot_Display)
  
  
## Ilitek-based displays:
ILI9225 
  * [Datasheet](https://www.displayfuture.com/Display/datasheet/controller/ILI9225.pdf)
  * [Tinkersphere breakout board](https://tinkersphere.com/arduino-compatible-components/336-tft-lcd-display-22-arduino-compatible.html) for this display
  * [ILI9225 library from Nkawu](https://github.com/Nkawu/TFT_22_ILI9225)

  
  
