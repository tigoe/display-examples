
/*
  Displays a clock on a DFRobot ST7687S round LCD display
  https://www.dfrobot.com/product-1794.html
  Written for the SAMD boards (MKR boards, Nano 33 IoT).

  Uses the  following libraries:
  - RTC library for the Arduino SAMD modules
  http://librarymanager/All#RTCZero.h
  - DFRobot DFRobot_ST7687S library for the round display
  https://github.com/DFRobot/DFRobot_ST7687S
  https://github.com/DFRobot/DFRobot_Display
  
  Circuit:
  - ST7687S 2.2" TFT round LCD display attached to the following pins:
  -- display SPI_SCK: pin 13
  -- display SPI_MOSI: pin 11
  -- display CS:  pin  10
  -- display RS:  pin 9
  -- display WR:  pin 8
  -- display LCK: pin 7

  created 24 April 2019
  updated 15 Jan 2021
  by Tom Igoe
*/
#include <DFRobot_ST7687S_Latch.h>
#include <SPI.h>
#include <RTCZero.h>

// output pins:
const int DISPLAY_CS = 10;
const int DISPLAY_RS = 9;
const int DISPLAY_WR = 8;
const int DISPLAY_LCK = 7;

// background color:
long bgColor = 0x335599;

// hand lengths:
int minuteHand = 40;
int secondHand = 50;
int hourHand = 25;

// initialize libraries:
DFRobot_ST7687S_Latch display(DISPLAY_CS, DISPLAY_RS, DISPLAY_WR, DISPLAY_LCK);
RTCZero rtc;

// last states of the second, minute, hour:
int lastSecond = 0;
int lastMinute = 0;
int lastHour = 0;

void setup() {
  // starrt the display and the clock:
  display.begin();
  rtc.begin();
  // set time from the compiler:
  setTimeFromCompile();
  display.fillScreen(bgColor);
}

void loop() {
  // redraw once per second:
  if (rtc.getSeconds() != lastSecond) {
    // if the hour has changed since last draw,
    // erase the old hour hand:
    if (rtc.getHours() != lastHour) {
      drawHand(lastHour, bgColor, hourHand, 12);
    }
    // draw the hour hand in white:
    drawHand(rtc.getHours(), 0xFFFFFF, hourHand, 12);
    lastHour = rtc.getHours() % 12;

    // if the minute has changed since last draw,
    // erase the old minute hand:
    if (rtc.getMinutes() != lastMinute) {
      drawHand(lastMinute, bgColor, minuteHand, 60);
    }
    // draw the minute hand:
    drawHand(rtc.getMinutes(), 0xFFFFFF, minuteHand, 60);
    lastMinute = rtc.getMinutes();

    // erase the old sedond hand:
    drawHand(lastSecond, bgColor, secondHand, 60);
    // draw the second hand:
    drawHand(rtc.getSeconds(), 0xFFFFFF, secondHand, 60);
    lastSecond = rtc.getSeconds();
  }
}

void drawHand(int handPosition, long handColor, int handLength, int divisions) {
  // calculate the angle based on the hand position:
  float angle = ((handPosition * 360.0) / divisions) ;
  // rotate 90 degrees counterclockwise:
  angle -= 90;
  // convert angle to radians:
  angle = angle * PI / 180;
  // calculate hand endpoint using Pythagorean theorem and hand length:
  float x = cos(angle) * handLength;
  float y = sin(angle) * handLength;
  // draw the line:
  display.drawLine(0, 0, x, y, handColor);
}

// set the rtc time from the compile time:
void setTimeFromCompile() {
  // get the compile time string:
  String compileTime = String(__TIME__);
  // break the compile time on the colons:
  int h = compileTime.substring(0, 2).toInt();
  int m = compileTime.substring(3, 5).toInt();
  int s = compileTime.substring(6, 8).toInt();

  // set the time from the derived numbers:
  rtc.setTime(h, m, s);
}
