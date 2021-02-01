# Displays for Microcontrollers

There are a number of different kinds of displays that can be driven by a microcontroller. This repository contains examples for many of them, along with information about display technologies and some of the more popular libraries for controlling them. 

## Display Technologies

Display technologies range from multi-segment LEDs through high-resolution, full-color displays. The major ones are detailed below.

**Multi-Segment LED display** - There are many models of multi-segment LED displays, including the classic 7-segment LEDs, alphanumeric displays, dot-matrix diplays, bar graph displays, RGB LEDs, and others. What these share in common is that they will have either a common-cathode or common-anode structure. Common cathode LEDs have multiple anodes, one for each LED segment, and one cathode for all. common anode LEDs have a single anode and multiple cathode for all the segments. Driving these displays requires a control pin for each LED segment. They are usually driven by a multiplexer or LED driver, which can provide both a common interface for all the LEDs (such as an SPI or I2C interface), and a controlled current supply for all the LEDs.  

[Broadcom/Avago's HCMS-29xx display](avago-display) is multi-segment LED display that has several 5-7 LED matrices with a synchronous serial interface.  It has the smallest visibly discrete LEDs in its display that I have encountered. 

**LCD** - Liquid crystal display. LCDs are made up of long-chain molecules in a state between crystal and liquid. When a charge is applied, the molecules align, acting as a polarizer. When paired with a second polarizer, they can either block light or allow it to pass through, appearing either light or dark. A grid of these can form a single-color display. Liquid crystals do not emit light, so a backlight is required to light them up. They come im low-resolution, passive-matrix displays which are usually monochrome or higher-resolution, active-matrix screens which have higher resolution and are usually full color.

**OLED** - an OLED screen replaces the liquid crystal with a matrix of organic LEDs. This eliminates the need for a backlight, since each pixel generates its own light. For more on OLEDs, see [this introduction](https://www.energy.gov/eere/ssl/oled-basics) from ehergy.gov. CNET provides this [comparison of LCD vs OLED displays](https://www.cnet.com/news/what-is-oled-and-what-can-it-do-for-your-tv/). 

**[ePaper](EPaper_Examples/)**  - ePaper displays use a matrix of tiny capsules which are black or colored on one side, and white on the other. Applying a charge to each capsule causes it to turn one way or the other. Unlike LCD or LED displays, ePaper displays maintain their state when powered off. ePaper displays cannot be refreshed as fast as LCD or LED, however. ePaper displays are typically not backlit, and require external lighting. eInk, the primary maker of ePaper displays, has a good [FAQ](https://www.eink.com/faqs.html) on the technology. Visionect.com has a helpful [illustrated explanation](https://www.visionect.com/blog/electronic-paper-explained-what-is-it-and-how-does-it-work/) as well. 

## Driver Technologies

There are a few common methods for driving displays, and a handful of popular manufacturers of driver integrated circuits (ICs). 

### Passive vs Active Matrix
LCD and OLED screens drive their pixels in one of two ways. A **passive matrix** uses a grid of wires which control each pixel using a row-column scanning method. Voltage is applied to each column in sequence. Then the rows are scanned. If the pixel on that column at a given row should be on, then the row wire voltage is taken low to create a voltage difference, and the pixel turns on. An **active matrix** uses a grid of **thin film transistors (TFT)** instead of a row-column scanning apparatus. TFTs allow for greater pixel density and therefore sharper image quality and better response time for each pixel. Jameco offers a good explanation of [passive vs. active matrix driver technology](https://www.jameco.com/Jameco/workshop/Howitworks/how-organic-light-emitting-diodes-work.html). 

For a more formal explanation of LCD and TFT displays, see [this page from J-Display](https://www.j-display.com/english/technology/lcdbasic.html)

The oldest form of LCD display, patented in the 1980's, is known as Twisted Nematic (TN) LCD, and has limits to its viewing angle. Newer LCD technologies such as [in-plane switching (IPS)](https://www.pctechguide.com/flat-panel-displays/ips-in-plane-switching-lcd-monitors) or [plane-to-line switching (PLS)](https://www.lifewire.com/definition-of-ips-lcd-578662) afford wider viewing angles and brighter screens.  

### Display Driver ICs
There are a number of common display driver ICs on the market. Typically a driver IC will be capable of controlling many different sizes and shapes of display, if they are of the same class. For example, you'll see many TFT displays that use [Sitronix' driver ICs](https://www.sitronix.com.tw/en/products/display-driver-ic/), notably the ST7735 and ST7789. Ilitek's [ILI9225](https://www.displayfuture.com/Display/datasheet/controller/ILI9225.pdf) chip is also common in TFTs. This means that libraries written for one vendor's display are likely to work for displays from another vendor, if they use the same chipset. This can be convenient, as it means you can sometimes choose the library whose API you find easiest to work with. 

### LED multi-segment driver ICs
There are many LED driver ICs on the market, which give you control over multiple LED segments from a single synchronous serial interface. Some include PWM control over each channel as well. Popular ones include Maxim's [MAX7219](https://www.maximintegrated.com/en/products/power/display-power-control/MAX7219.html) and Texas Instruments' [TLC5947](https://www.ti.com/product/TLC5947). Many of the hobbyist electronic vendors carry breakout boards for these chips. 

### Addressable LEDs
Recently, drivers for LEDs have reduced in size to the point where a driver can drive a single pixel. Usually made of three to four LEDs and a single driver, these are very popular with electronics hobbyists. For more on these, see [this repository](https://tigoe.github.io/LightProjects/addressable-leds.html).  

## Control Protocols
Displays for microcontrollers use a variety of control interfaces. The most common are the ones you see for other electronic modules as well: synchronous serial interfaces like I2C and SPI, or asynchronous serial interfaces. also feature parallel interface, requires a large number of I/O pins from your controller. 

### SPI
Typically a display with an SPI interface will feature most or all of the following pins:
* Voltage - Microcontroller voltage supply. 3.3V or 5V voltage, depending on the display
* Ground - Microcontoller ground
* SDI - Serial Data in. Connects to the microcontrollers SPI SDO pin
* SCK - Serial Clock. Connects to the microcontroller's SPI clock pin
* CS - Chip Select. Connects to the microcontroller's SPI CS pin
* D/C - Data/Command. Connects to whatever pin the microcontroller has assigned for this function.
* RESET - a reset pin, connects to whicheve pin the microcontroller has assigned for this function.
* BUSY - an output pin to indicate that the display controller is busy. connects to whicheve pin the microcontroller has assigned for this function.

### I2C
Displays with I2C interfaces typically have the following pinouts:
* SDA - Serial data, connects to the microcontroller's I2C SDA pin
* SCL - Serial clock, connects to the microcontroller's I2C SCL pin
* RESET - a reset pin, connects to whicheve pin the microcontroller has assigned for this function. Not all screens implement this pin. 

 * [SSD1306](SSD1306_OLED_Examples/)

### Parallel
 * LCD Display - Hitachi HD44780 driver. See [LiquidCrystal library](https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
 * LED Matrix
 * 7-segment LED displays

### Asynchronous Serial
There are some display modules which have an asynchronous serial (UART) interfaces. These typically have a microcontroller on the display module itself, which is interfacing with one of the types of interfaces above. These modules typically have a communications protocol that is unique to the vendor. They are convenient, but more expensive than their synchronous serial or parallel counterparts. 