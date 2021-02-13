# TFT LCD Displays

There are a few common TFT display drivers on the electronics hobbyist market, and a handful of libraries that work with them. TFT displays are high resolution and full color, unlike the OLED or ePaper displays mentioned in this repository. 

You can find the [code examples at this link](https://github.com/tigoe/display-examples/tree/main/TFT_Examples).

## Hardware
The TFT boards I have encountered so far have had either Sitronix or Ilitek interfaces. The models are detailed below. 

### Pin Connections
Most TFT displays tend to have an SPI interface, with some extra pins, as explained on the [main page](../readme.md#spi-connections) of this repo. Some displays, like MakerFocus' 1.3" TFT, do not implement the CS pin. For this board and others like it, initializing them with `SPI_MODE3` works.

### Sitronix ST7735 and ST7789 TFT Displays
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
  
  
### Ilitek-based displays:
ILI9225 
  * [Datasheet](https://www.displayfuture.com/Display/datasheet/controller/ILI9225.pdf)
  * [Tinkersphere breakout board](https://tinkersphere.com/arduino-compatible-components/336-tft-lcd-display-22-arduino-compatible.html) for this display
  * [ILI9225 library from Nkawu](https://github.com/Nkawu/TFT_22_ILI9225)

## Libraries
There's no standard library for TFT screens, unfortunately. Vendors tend to support the displays they make in their own breakout boards, and not others. As with other types of displays, a well-supported library like the Adafruit libraries makes the display worth more, but limits you to the types of displays that vendor offers. Display manufacturers like Ilitek and Sitronix do not appear to release their own libraries for their displays.

### ST7735/7789
The Adafruit_ST7735/7789 library and Adafruit_GFX library works well with some of the Sitronix boards above. It does not support the DFRobot ST7867S board, however. 

### ST7687S
The DFRobot_ST7687S library has slow refresh rate on the ST7687S board. It's unclear whether the issue is the library or the board, however. I have yet to find another library to use with this display, though there are a couple other vendors for the board itself on Amazon. Unfortunately the u8g2 library doesn't support this display, though it does support many of the Sitronix boards.

### ILI9225
The TFT_22_ILI9225 for the Ilitek works fairly well with the display, though its graphics API is different than some of the other graphics libraries, and doesn't implement the Printable API, so you can't use commands like `print()` and `println()` with it. 



  
  
