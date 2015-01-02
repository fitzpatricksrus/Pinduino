#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 32;

#define USE_SPI
#ifdef USE_SPI
// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Use hardware SPI
LPD8806 strip = LPD8806(nLEDs);

#else

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 7;
int clockPin = 8;
// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
#endif
// You can optionally use hardware SPI for faster writes, just leave out
// the data and clock pin parameters.  But this does limit use to very
// specific pins on the Arduino.  For "classic" Arduinos (Uno, Duemilanove,
// etc.), data = pin 11, clock = pin 13.  For Arduino Mega, data = pin 51,
// clock = pin 52.  For 32u4 Breakout Board+ and Teensy, data = pin B2,
// clock = pin B1.  For Leonardo, this can ONLY be done on the ICSP pins.
//LPD8806 strip = LPD8806(nLEDs);

void setup() {

  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}

static uint8_t BRT = 127;
static uint16_t WAIT_TIME = 50;

void loop() {
#if 1
  // Fill the entire strip with...
#if 1
  colorWipe(strip.Color(BRT,   0,   0), WAIT_TIME);  // Red
  colorWipe(strip.Color(  0, BRT,   0), WAIT_TIME);  // Green
  colorWipe(strip.Color(  0,   0, BRT), WAIT_TIME);  // Blue

  // Send a simple pixel chase in...
  colorChase(strip.Color(BRT, BRT, BRT), WAIT_TIME); // White
  colorChase(strip.Color(BRT,   0,   0), WAIT_TIME); // Red
  colorChase(strip.Color(BRT, BRT,   0), WAIT_TIME); // Yellow
  colorChase(strip.Color(  0, BRT,   0), WAIT_TIME); // Green
  colorChase(strip.Color(  0, BRT, BRT), WAIT_TIME); // Cyan
  colorChase(strip.Color(  0,   0, BRT), WAIT_TIME); // Blue
  colorChase(strip.Color(BRT,   0, BRT), WAIT_TIME); // Violet

  // Send a theater pixel chase in...
  theaterChase(strip.Color(BRT, BRT, BRT), WAIT_TIME); // White
  theaterChase(strip.Color(BRT,   0,   0), WAIT_TIME); // Red
  theaterChase(strip.Color(BRT, BRT,   0), WAIT_TIME); // Yellow
  theaterChase(strip.Color(  0, BRT,   0), WAIT_TIME); // Green
  theaterChase(strip.Color(  0, BRT, BRT), WAIT_TIME); // Cyan
  theaterChase(strip.Color(  0,   0, BRT), WAIT_TIME); // Blue
  theaterChase(strip.Color(BRT,   0, BRT), WAIT_TIME); // Violet
#endif

  rainbow(50);
  rainbowCycle(5);  // make it go through the cycle fairly fast
  theaterChaseRainbow(50);
}

void rainbow(uint16_t wait) {
  int i, j;

  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
    }
    strip.show();   // write all the pixels out
    delay(wait);
  }
#endif
}

// Slightly different, this one makes the rainbow wheel equally distributed
// along the chain
void rainbowCycle(uint16_t wait) {
  uint16_t i, j;

  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint16_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint16_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint16_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint16_t wait) {
  for (int j=0; j < 384; j++) {     // cycle all 384 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 384));    //turn every third pixel on
        }
        strip.show();

        delay(wait);

        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break;
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break;
    case 2:
      b = 127 - WheelPos % 128;  //blue down
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break;
  }
  return(strip.Color(r,g,b));
}
