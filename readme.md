# Displays for Microcontrollers

There are a number of different kinds of displays that can be driven by a microcontroller. Listed here are a few of the more common ones, and some explanations of the terminology used to describe them. 

## Display Technologies

**Multi-Segment LED display** - There are many models of multi-segment LED displays, including the classic 7-segment LEDs, alphanumeric displays, dot-matrix diplays, bar graph displays, RGB LEDs, and others. What these share in common is that they will have either a common-cathode or common-anode structure. Common cathode LEDs have multiple anodes, one for each LED segment, and one cathode for all. common anode LEDs have a single anode and multiple cathode for all the segments. Driving these displays requires a control pin for each LED segment. They are usually driven by a multiplexer or LED driver, which can provide both a common interface for all the LEDs (such as an SPI or I2C interface), and a controlled current supply for all the LEDs.

**LCD** - Liquid crystal display. LCDs are made up of long-chain molecules in a state between crystal and liquid. When a charge is applied, the molecules align, acting as a polarizer. When paired with a second polarizer, they can either block light or allow it to pass through, appearing either light or dark. A grid of these can form a single-color display. Liquid crystals do not emit light, so a backlight is required to light them up. 

**OLED** - an OLED screen replaces the liquid crystal with a matrix of organic LEDs. This eliminates the need for a backlight, since each pixel generates its own light. For more on OLEDs, see [this introduction](https://www.energy.gov/eere/ssl/oled-basics) from ehergy.gov. CNET provides this [comparison of LCD vs OLED displays](https://www.cnet.com/news/what-is-oled-and-what-can-it-do-for-your-tv/). 

**ePaper**  - ePaper displays use a matrix of tiny capsules which are black or colored on one side, and white on the other. Applying a charge to each capsule causes it to turn one way or the other. Unlike LCD or LED displays, ePaper displays maintain their state when powered off. ePaper displays cannot be refreshed as fast as LCD or LED, however. ePaper displays are typically not backlit, and require external lighting. eInk, the primary maker of ePaper displays, has a good [FAQ](https://www.eink.com/faqs.html) on the technology. Visionect.com has a helpful [illustrated explanation](https://www.visionect.com/blog/electronic-paper-explained-what-is-it-and-how-does-it-work/) as well. 

## Driver Technologies

**Passive vs Active Matrix**- LCD and OLED screens drive their pixels in one of two ways. A **passive matrix** uses a grid of wires which control each pixel using a row-column scanning method. Voltage is applied to each column in sequence. Then the rows are scanned. If the pixel on that column at a given row should be on, then the row wire voltage is taken low to create a voltage difference, and the pixel turns on. An **active matrix** uses a grid of **thin film transistors (TFT)** instead of a row-column scanning apparatus. TFTs allow for greater pixel density and therefore sharper image quality and better response time for each pixel. Jameco offers a good explanation of [passive vs. active matrix driver technology](https://www.jameco.com/Jameco/workshop/Howitworks/how-organic-light-emitting-diodes-work.html). 

For a more formal explanation of LCD and TFT displays, see [this page from J-Display](https://www.j-display.com/english/technology/lcdbasic.html)

The oldest form of LCD display, patented in the 1980's, is known as Twisted Nematic (TN) LCD, and has limits to its viewing angle. Newer LCD technologies such as [in-plane switching (IPS)](https://www.pctechguide.com/flat-panel-displays/ips-in-plane-switching-lcd-monitors) or [plane-to-line switching (PLS)](https://www.lifewire.com/definition-of-ips-lcd-578662) afford wider viewing angles and brighter screens.  

**LED driver ICs** There are many LED driver ICs on the market, which give you control over multiple LED segments from a single synchronous serial interface. Some include PWM control over each channel as well. Popular ones include Maxim's [MAX7219](https://www.maximintegrated.com/en/products/power/display-power-control/MAX7219.html) and Texas Instruments' [TLC5947](https://www.ti.com/product/TLC5947). Many of the hobbyist electronic vendors carry breakout boards for these chips. 

## Control Interfaces

Displays for microcontrollers use a variety of control interfaces. The most common are the ones you see for other electronic modules as well: synchronous serial interfaces like I2C and SPI, or asynchronous serial interfaces.

### SPI
 * ST7687S round LCD display from DFRobot -- see clock club repo
 * TFT displays - [TFT Library](https://www.arduino.cc/reference/en/libraries/tft/) based on ST7735 chipset
 * ILI9225 TFT display -- see clock club repo
 * [ePaper](EPaper_examples/)

### I2C
 * SSD1306

### Parallel
 * LCD Display - Hitachi HD44780 driver. See [LiquidCrystal library](https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
 * LED Matrix
 * 7-segment LED displays
 * [Avago HCMS-29xx](https://www.arduino.cc/reference/en/libraries/leddisplay/)

### Asynchronous Serial
 * Many of these are serial backpacks on LCD displays