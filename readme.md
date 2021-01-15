# Screens for Microcontrollers

There are a number of different kinds of sceeens that can be driven by a microcontroller. Listed here are a few of the more common ones, and some explanations of the terminology used to describe them. 

## Display Technologies

**LCD** - Liquid crystal display. LCDs are made up of long-chain molecules in a state between crystal and liquid. When a charge is applied, the molecules align, acting as a polarizer. When paired with a second polarizer, they can either block light or allow it to pass through, appearing either light or dark. A grid of these can form a single-color display. Liquid crystals do not emit light, so a backlight is required to light them up. 

**OLED** - an OLED screen replaces the liquid crystal with a matrix of organic LEDs. This eliminates the need for a backlight, since each pixel generates its own light. For more on OLEDs, see [this introduction](https://www.energy.gov/eere/ssl/oled-basics) from ehergy.gov. CNET provides this [comparison of LCD vs OLED displays](https://www.cnet.com/news/what-is-oled-and-what-can-it-do-for-your-tv/). 

**ePaper**  - ePaper displays use a matrix of tiny capsules which are black or colored on one side, and white on the other. Applying a charge to each capsule causes it to turn one way or the other. Unlike LCD or LED displays, ePaper displays maintain their state when powered off. ePaper displays cannot be refreshed as fast as LCD or LED, however. ePaper displays are typically not backlit, and require external lighting. eInk, the primary maker of ePaper displays, has a good [FAQ](https://www.eink.com/faqs.html) on the technology. Visionect.com has a helpful [illustrated explanation](https://www.visionect.com/blog/electronic-paper-explained-what-is-it-and-how-does-it-work/) as well. 

## Driver Technologies

**Passive vs Active Matrix**- LCD and OLED screens drive their pixels in one of two ways. A **passive matrix** uses a grid of wires which control each pixel using a row-column scanning method. Voltage is applied to each column in sequence. Then the rows are scanned. If the pixel on that column at a given row should be on, then the row wire voltage is taken low to create a voltage difference, and the pixel turns on. An **active matrix** uses a grid of **thin film transistors (TFT)** instead of a row-column scanning apparatus. TFTs allow for greater pixel density and therefore sharper image quality and better response time for each pixel. Jameco offers a good explanation of [passive vs. active matrix driver technology](https://www.jameco.com/Jameco/workshop/Howitworks/how-organic-light-emitting-diodes-work.html). 

For a more formal explanation of LCD and TFT displays, see [this page from J-Display](https://www.j-display.com/english/technology/lcdbasic.html)

The oldest form of LCD display, patented in the 1980's, is known as Twisted Nematic (TN) LCD, and has limits to its viewing angle. Newer LCD technologies such as [in-plane switching (IPS)](https://www.pctechguide.com/flat-panel-displays/ips-in-plane-switching-lcd-monitors) or [plane-to-line switching (PLS)](https://www.lifewire.com/definition-of-ips-lcd-578662) afford wider viewing angles and brighter screens.  

LED Matrix, 7-segment and alphanumeric, addressable LED
MAX7219 and other LED multiplexers

## Control Methods


### SPI
 * ST7687S round LCD display from DFRobot -- see clock club repo
 * TFT displays - [TFT Library](https://www.arduino.cc/reference/en/libraries/tft/) based on ST7735 chipset
 * ILI9225 TFT display -- see clock club repo
 * EInk

### I2C
 * SSD1306

### Parallel
 * LCD Display - Hitachi HD44780 driver. See [LiquidCrystal library](https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
 * LED Matrix
 * 7-segment LED displays
 * [Avago HCMS-29xx](https://www.arduino.cc/reference/en/libraries/leddisplay/)

### Asynchronous Serial
 * Many of these are serial backpacks on LCD displays