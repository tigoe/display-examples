# Inventory

A list of components mentioned in this repository.

## Multiplexers and PWM drivers

| Item | Vendor 1 | Vendor 2 | Notes| 
|--|--|--|--|
| [TLC5947 PWM driver](https://www.ti.com/lit/ds/symlink/tlc5947.pdf) | [Adafruit](https://www.adafruit.com/product/1429) | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/1429/5353645)  | This IC comes in many other form factors and breakout boards, and there are multiple libraries for it. |

## TFT LCD Displays

| Item | Vendor 1 | Vendor 2 | Notes | 
|---------|---------|---------|---------|
| 1.54" 240x240 Wide Angle TFT LCD Display with MicroSD  | [Adafruit](https://www.adafruit.com/product/3787) | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/3787/8627476) | Breakout board with ST7789 driver IC |
| 1.14" 240x135 Color TFT Display with MicroSD | [Adafruit](https://www.adafruit.com/product/4383) | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4383/10650642) | Breakout board with ST7789 driver IC |
| 1.3" TFT LCD Display, no MicroSD | [MakerFocus](https://bit.ly/3qDYMLo) | [Amazon](https://smile.amazon.com/gp/product/B07P9X3L7M) | Breakout board with ST7789 driver IC. This display does not have a CS pin, so it can't be used with other SPI devices at the same time. To use it with the Adafruit_7735/7789 library, init using `SPI_MODE3` |
| 2.2” Round TFT LCD Display | [DFRobot](https://www.dfrobot.com/product-1794.html) |[Digikey](https://www.digikey.com/en/products/detail/dfrobot/DFR0529/9739905) | Color TFT display |

## OLED Displays

| Item | Vendor 1 | Vendor 2 | Notes |  
|--|--|--|--|
| Micro OLED | [Sparkfun](https://www.sparkfun.com/products/13003) | [Digikey](https://www.digikey.com/en/products/detail/sparkfun-electronics/LCD-13003/5673774) | Breakout board. Does not work with the other SSD1306 libraries.  | 
| SSD1306 0.91" 128x32 I2C interface | [MakerFocus](https://www.makerfocus.com/collections/oled/products/2pcs-i2c-oled-display-module-0-91-inch-i2c-ssd1306-oled-display-module-1) | [Amazon](https://smile.amazon.com/gp/product/B079BN2J8V) | Breakout board, Qty. 2| 
| SSD1306 0.96" 128x64 |  [MakerFocus](https://www.makerfocus.com/collections/oled/products/4pcs-i2c-oled-0-96-inch-display-module-with-du-pont-wire-40-pin-for-arduino-uno-r3-stm) | [Amazon](https://smile.amazon.com/Display-Module-SSD1306-Du-pont-Arduino/dp/B07VDXYDVY) | Breakout board, Qty. 4 | 
| 128x128 Round OLED display  | [Crystalfontz](https://www.crystalfontz.com/product/cfal128128b0011w-128x128-round-oled-display) | - | Bare display, needs driver board, 24-position 0.5mm pitch ZIF connector and voltage converter circuit | 
| 128x56 Transparent OLED Display | [Crystalfontz](https://www.crystalfontz.com/product/cfal12856a00151b-128x56-transparent-oled-screen) | - | Bare display, needs driver board, 24-position 0.5mm pitch ZIF connector and voltage converter circuit. Works with breakout board below.  |
| OLED Breakout Board | [Crystalfontz](https://www.crystalfontz.com/product/cfa10105-oled-breakout-board) | - | Supports 24-position 0.5mm pitch ZIF connector transparend OLED boards, but not the round ones above. |  

## ePaper Displays

| Item | Vendor 1 | Vendor 2 | Notes | 
|--|--|--|--|
| 1.54" Monochrome ePaper Display with SRAM - 200x200 | [Adafruit](https://www.adafruit.com/product/4196) | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4196/10060722) | Breakout board |
| 1.54" Tri-Color eInk / ePaper Display with SRAM - 152x152- Red Black White | [Adafruit](https://www.adafruit.com/product/3625) |  [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/3625/9489367) | Breakout board  |
| SHARP Memory Display Breakout - 1.3" 168x144 Monochrome | [Adafruit](https://www.adafruit.com/product/3502) | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/3502/7386264) | Breakout board. Not an actual ePaper display, though it looks like one. The image fades when you remove power, but it retains for a few second. The display rate is more like an LCD. |
| eInk Breakout Friend with 32KB SRAM | [Adafruit](https://www.adafruit.com/product/4224) | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4224/10107219) | Driver board, no display Supports multiple bare ePaper displays, including ones not from Adafruit |
| ePaper Adapter Board | [Crystalfontz](https://www.crystalfontz.com/product/cfa10084-epaper-adapter-board) | - | supports 24-position 0.5mm pitch ZIF connector displays. I have yet to get this to work with the Adafruit_EPD library. |
|  1.54" 152x152 3-color breakout  | [Sparkfun](https://www.sparkfun.com/products/retired/14892)| -| Breakout board, discontinued |
| 1.54" panel, 200x200 | [WaveShare](https://www.waveshare.com/1.54inch-e-paper-module-b.htm) | [Amazon](https://smile.amazon.com/Tri-Color-Three-Color-Resolution-Electronic-Controller/dp/B0751NSSPV) | Tricolor (Black/white/red).  doesn't have SRAM or SD card |
| 1.54" 3-Color display | [Crystalfontz](https://www.crystalfontz.com/product/cfap152152b00154-3-color-epaper-module) | - | Black/white/yellow. Bare display, needs driver board, 24-position 0.5mm pitch ZIF connector |  
| 2.13" panel, 250x122 for Raspberry Pi | [WaveShare](https://www.waveshare.com/product/displays/e-paper/epaper-3/2.13inch-e-paper-hat.htm) | [Amazon](https://smile.amazon.com/gp/product/B071S8HT76) | Breakout board w/cable | 
| 2.13" Flexible Monochrome eInk Display - 212x104 |[Adafruit](https://www.adafruit.com/product/4243) | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4243/10229998) | bare display, needs driver | 

## Multi-Segment LED Displays

| Item | Vendor 1 | Vendor 2 | Notes | 
|--|--|--|--|
|[Broadcom/Avago 5x7-pixel LED displays](https://www.broadcom.com/products/leds-and-displays/smart-alphanumeric-displays/serial-interface) |[Mouser](https://www.mouser.com/Optoelectronics/Displays/LED-Displays-Accessories/_/N-6j73b?P=1yzvvp2&Keyword=HCMS-29&FS=True) | [Digikey](https://www.digikey.com/en/products/filter/display-modules-led-dot-matrix-and-cluster/96?s=N4IgjCBcpgnAHLKoDGUBmBDANgZwKYA0IA9lANogAMIAusQA4AuUIAykwE4CWAdgOYgAvsQC0AFmQg0kLHiKkK4AGywAzAFY6jFpBDCRIAExKAQpxKYAJihIBbAAQAJAMIBZNkaS0hQA) | Newer models of these displays may also work with [this library](https://playground.arduino.cc/Main/LedDisplay/). |
| [8x8 LED Displays](LED_8x8_Matrix_examples/readme.md)| [Digikey](https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/104020149/10451891) (red) | [Digikey](https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/104020150/10451906) (blue) | There are many different colors, models and manufacturers of these, this is just one example. Search any major vendor for others. |


## Display Vendors

* [Adafruit](https://www.adafruit.com/?q=display&sort=BestMatch)
* [Sparkfun](https://www.sparkfun.com/search/results?term=display)
* [Seeed Studio](https://www.seeedstudio.com/catalogsearch/result/?q=display)
* [DFRobot](https://www.dfrobot.com/search-display.html)
* [WaveShare](https://www.waveshare.com/product/displays.htm) -  note: WaveShare supplies parts mainly through Amazon, and their dire
* [MakerFocus](https://www.makerfocus.com/collections/display) - note: MakerFocus supplies parts mainly through Amazon, and their direct delivery is not fast. 
* [Tinkersphere](https://tinkersphere.com/search?controller=search&orderby=position&orderway=desc&search_query=display&submit_search=Search)
* [CrystalFontz](https://www.crystalfontz.com/)