# Broadcom/Avago Serial LED Display
Avago, now a part of Broadcom, makes a series of multi-character serial [5x7-pixel LED displays](https://www.broadcom.com/products/leds-and-displays/smart-alphanumeric-displays/serial-interface). These are small and pretty displays, available in 4-character, 8- and 16-character models. They are quite expensive relative to other displays, and not common as a result.

![Photo of a Broadcom/Avago HCMS29xx display attached to an Arduino Uno](https://playground.arduino.cc/uploads/Main/HCMs297x/index.png)
_Figure 1. Broadcom/Avago HCMS29xx display attached to an Arduino Uno. These displays have a wide supply voltage range, and run on both 5V and 3.3V boards. Photo by me, on the Arduino site._

## Pin Connections
The HCMS-29xx displays require the following pin connections from your microcontroller. You can use any of the pins of your controller for these pins, and they are generally defined at the top of your code:

* Data - the synchronous serial data pin
* Clock - the synchronous serial clock pin
* Register Select - selects which memory register of the display you are addressing
* Enable - the pin that enables the display
* Reset - the display reset

There are also four voltage pins and three ground pins for this display.  These displays can be daisy-chained so that you can control multiple displays from the same pins.

![HCMS-29xx pin diagram](https://www.pjrc.com/teensy/td_libs_LedDisplay_2.gif)
_Figure 2. The HCMS-29xx display pin diagram. Image from Paul Stoffregen's library page for this display._

## Communications Protocol
These displays have a proprietary synchronous serial data interface which is detailed in the data sheet for the series. The Arduino [LedDisplay library](https://playground.arduino.cc/Main/LedDisplay/) can control them. Paul Stoffregen currently maintains the library and has an [excellent page with the pin wiring and details](https://www.pjrc.com/teensy/td_libs_LedDisplay.html). The examples included with the library install give examples of what the library supports, and you can find a [clock example](https://github.com/ITPNYU/clock-club/blob/master/RTC_Clock_Examples/RTCClockAvagoDisplay/RTCClockAvagoDisplay.ino) on the [Clock Club](https://github.com/itpnyu/clock-club) repository as well. 
