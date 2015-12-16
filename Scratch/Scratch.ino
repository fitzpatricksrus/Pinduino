/*

#include <Arduino.h>


#include "FastLED.h"

static const int NUM_LEDS = 50;
CRGB leds[NUM_LEDS];

void setup() {
	Serial.begin(57600);
	pinMode(13, OUTPUT);
    FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
}

void loop() {
//	for (int i = 0; i < NUM_LEDS; i++) {
//		leds[i] = CRGB::White; FastLED.show();
//	}
//	delay(50);
//	for (int i = 0; i < NUM_LEDS; i++) {
//		leds[i] = CRGB::Black; FastLED.show();
//	}

 //   leds[0] = CRGB::Black; FastLED.show(); delay(300);
	  static uint8_t hue = 0;
	  FastLED.showColor(CHSV(hue++, 255, 128));
	  delay(15);
}

*/

#define LED_PIN     13
#define DATA_PIN     13
#define NUM_LEDS    199
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define LED_TYPE    WS2811

#define colorpalleteX
#define fireX
#define firewithpalletteX
#define noisePlusPalletteX
#define demoReel
#define campFireX


#ifdef colorpallete
#include <FastLED.h>

#define BRIGHTNESS  64
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    ChangePalettePeriodically();

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors( startIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;

    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;

    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,

    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};



// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
#endif

#ifdef fire

#include <FastLED.h>

#define BRIGHTNESS  200
#define UPDATES_PER_SECOND 60

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  // random16_add_entropy( random());

  Fire2012(); // run simulation frame

  FastLED.show(); // display this frame
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
////
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation,
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120


void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

#endif

#ifdef firewithpallette
#include <FastLED.h>

//#define LED_PIN     13
//#define COLOR_ORDER RGB
//#define CHIPSET     WS2811
//#define NUM_LEDS    99

#define BRIGHTNESS  200
#define UPDATES_PER_SECOND 100

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];

// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
// Four different static color palettes are provided here, plus one dynamic one.
//
// The three static ones are:
//   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
//      pretty much exactly like the original Fire2012.
//
//  To use any of the other palettes below, just "uncomment" the corresponding code.
//
//   2. a gradient from black to red to yellow to white, which is
//      visually similar to the HeatColors_p, and helps to illustrate
//      what the 'heat colors' palette is actually doing,
//   3. a similar gradient, but in blue colors rather than red ones,
//      i.e. from black to blue to aqua to white, which results in
//      an "icy blue" fire effect,
//   4. a simplified three-step gradient, from black to red to white, just to show
//      that these gradients need not have four components; two or
//      three are possible, too, even if they don't look quite as nice for fire.
//
// The dynamic palette shows how you can change the basic 'hue' of the
// color palette every time through the loop, producing "rainbow fire".

CRGBPalette16 gPal;

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  gPal = HeatColors_p;

  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);

  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);

  // Third, here's a simpler, three-step gradient, from black to red to white
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);

}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  // Fourth, the most sophisticated: this one sets up a new palette every
  // time through the loop, based on a hue that changes every time.
  // The palette is a gradient from black, to a dark color based on the hue,
  // to a light color based on the hue, to white.
  //
  //   static uint8_t hue = 0;
  //   hue++;
  //   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
  //   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
  //   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);


  Fire2012WithPalette(); // run simulation frame, using palette colors

  FastLED.show(); // display this frame
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
////
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation,
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120


void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
#endif

//---------------------------------------------------------------
#ifdef noisePlusPallette
#include<FastLED.h>

//#define LED_PIN     13
//#define BRIGHTNESS  96
//#define LED_TYPE    WS2811
//#define COLOR_ORDER RGB

const uint8_t kMatrixWidth  = 7;
const uint8_t kMatrixHeight = 7;
const bool    kMatrixSerpentineLayout = true;


// This example combines two features of FastLED to produce a remarkable range of
// effects from a relatively small amount of code.  This example combines FastLED's
// color palette lookup functions with FastLED's Perlin/simplex noise generator, and
// the combination is extremely powerful.
//
// You might want to look at the "ColorPalette" and "Noise" examples separately
// if this example code seems daunting.
//
//
// The basic setup here is that for each frame, we generate a new array of
// 'noise' data, and then map it onto the LED matrix through a color palette.
//
// Periodically, the color palette is changed, and new noise-generation parameters
// are chosen at the same time.  In this example, specific noise-generation
// values have been selected to match the given color palettes; some are faster,
// or slower, or larger, or smaller than others, but there's no reason these
// parameters can't be freely mixed-and-matched.
//
// In addition, this example includes some fast automatic 'data smoothing' at
// lower noise speeds to help produce smoother animations in those cases.
//
// The FastLED built-in color palettes (Forest, Clouds, Lava, Ocean, Party) are
// used, as well as some 'hand-defined' ones, and some proceedurally generated
// palettes.


#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)

// The leds
CRGB leds[kMatrixWidth * kMatrixHeight];

// The 16 bit version of our coordinates
static uint16_t x;
static uint16_t y;
static uint16_t z;

// We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// use the z-axis for "time".  speed determines how fast time moves forward.  Try
// 1 for a very slow moving effect, or 60 for something that ends up looking like
// water.
uint16_t speed = 20; // speed is set dynamically once we've started up

// Scale determines how far apart the pixels in our noise matrix are.  Try
// changing these values around to see how it affects the motion of the display.  The
// higher the value of scale, the more "zoomed out" the noise iwll be.  A value
// of 1 will be so zoomed in, you'll mostly see solid colors.
uint16_t scale = 30; // scale is set dynamically once we've started up

// This is the array that we keep our computed noise values in
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

CRGBPalette16 currentPalette( PartyColors_p );
uint8_t       colorLoop = 1;

void setup() {
  delay(3000);
  LEDS.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  LEDS.setBrightness(BRIGHTNESS);

  // Initialize our coordinates to some random values
  x = random16();
  y = random16();
  z = random16();
}



// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8() {
  // If we're runing at a low "speed", some 8-bit artifacts become visible
  // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  // The amount of data smoothing we're doing depends on "speed".
  uint8_t dataSmoothing = 0;
  if( speed < 50) {
    dataSmoothing = 200 - (speed * 4);
  }

  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;

      uint8_t data = inoise8(x + ioffset,y + joffset,z);

      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      data = qsub8(data,16);
      data = qadd8(data,scale8(data,39));

      if( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }

      noise[i][j] = data;
    }
  }

  z += speed;

  // apply slow drift to X and Y, just for visual variation.
  x += speed / 8;
  y -= speed / 16;
}

void mapNoiseToLEDsUsingPalette()
{
  static uint8_t ihue=0;

  for(int i = 0; i < kMatrixWidth; i++) {
    for(int j = 0; j < kMatrixHeight; j++) {
      // We use the value at the (i,j) coordinate in the noise
      // array for our brightness, and the flipped value from (j,i)
      // for our pixel's index into the color palette.

      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];

      // if this palette is a 'loop', add a slowly-changing base value
      if( colorLoop) {
        index += ihue;
      }

      // brighten up, as the color palette itself often contains the
      // light/dark dynamic range desired
      if( bri > 127 ) {
        bri = 255;
      } else {
        bri = dim8_raw( bri * 2);
      }

      CRGB color = ColorFromPalette( currentPalette, index, bri);
      leds[XY(i,j)] = color;
    }
  }

  ihue+=1;
}

void loop() {
  // Periodically choose a new palette, speed, and scale
  ChangePaletteAndSettingsPeriodically();

  // generate noise data
  fillnoise8();

  // convert the noise data to colors in the LED array
  // using the current palette
  mapNoiseToLEDsUsingPalette();

  LEDS.show();
  // delay(10);
}



// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.

// 1 = 5 sec per palette
// 2 = 10 sec per palette
// etc
#define HOLD_PALETTES_X_TIMES_AS_LONG 1

void ChangePaletteAndSettingsPeriodically()
{
  uint8_t secondHand = ((millis() / 1000) / HOLD_PALETTES_X_TIMES_AS_LONG) % 60;
  static uint8_t lastSecond = 99;

  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    if( secondHand ==  0)  { currentPalette = RainbowColors_p;         speed = 20; scale = 30; colorLoop = 1; }
    if( secondHand ==  5)  { SetupPurpleAndGreenPalette();             speed = 10; scale = 50; colorLoop = 1; }
    if( secondHand == 10)  { SetupBlackAndWhiteStripedPalette();       speed = 20; scale = 30; colorLoop = 1; }
    if( secondHand == 15)  { currentPalette = ForestColors_p;          speed =  8; scale =120; colorLoop = 0; }
    if( secondHand == 20)  { currentPalette = CloudColors_p;           speed =  4; scale = 30; colorLoop = 0; }
    if( secondHand == 25)  { currentPalette = LavaColors_p;            speed =  8; scale = 50; colorLoop = 0; }
    if( secondHand == 30)  { currentPalette = OceanColors_p;           speed = 20; scale = 90; colorLoop = 0; }
    if( secondHand == 35)  { currentPalette = PartyColors_p;           speed = 20; scale = 30; colorLoop = 1; }
    if( secondHand == 40)  { SetupRandomPalette();                     speed = 20; scale = 20; colorLoop = 1; }
    if( secondHand == 45)  { SetupRandomPalette();                     speed = 50; scale = 50; colorLoop = 1; }
    if( secondHand == 50)  { SetupRandomPalette();                     speed = 90; scale = 90; colorLoop = 1; }
    if( secondHand == 55)  { currentPalette = RainbowStripeColors_p;   speed = 30; scale = 20; colorLoop = 1; }
  }
}

// This function generates a random palette that's a gradient
// between four different colors.  The first is a dim hue, the second is
// a bright hue, the third is a bright pastel, and the last is
// another bright hue.  This gives some visual bright/dark variation
// which is more interesting than just a gradient of different hues.
void SetupRandomPalette()
{
  currentPalette = CRGBPalette16(
                      CHSV( random8(), 255, 32),
                      CHSV( random8(), 255, 255),
                      CHSV( random8(), 128, 255),
                      CHSV( random8(), 255, 255));
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black );
}


//
// Mark's xy coordinate mapping code.  See the XYMatrix for more information on it.
//
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }
  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  return i;
}
#endif

//---------------------------------------------------------------

#ifdef demoReel

#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

//#define DATA_PIN    13
//#define CLK_PIN   4
//#define LED_TYPE    WS2811
//#define COLOR_ORDER RGB
//#define NUM_LEDS    99
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define UPDATES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { solid, rainbow, rainbowWithGlitter, confetti, sinelon, juggle, confetti /*, bpm */ };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/UPDATES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 20 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void solid()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 0);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter)
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

#endif

// -----------------------------------------------------------------
#ifdef campFire

//
// Copyright (c) 2013 Danny Havenith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
/**
 * Simulation of a campfire using a WS2811 led string.
 * This code creates a campfire-like pattern by spacing 'flames' over the led string.
 * Each flame is a simple sequence that moves from dark and red-ish to light and yellow-ish and back.
 * The animation consists of letting each flame perform a random walk over the led string, adding
 * intensities where two flames overlap.
 * When the led string is curled up in a ball-shape and placed under a diffusing cover, this gives
 * a reasonably realistic fire animation.
 */

//#define DATA_PIN    13
//#define CLK_PIN   4
//#define LED_TYPE    WS2811
//#define COLOR_ORDER RGB
//#define NUM_LEDS    50
CRGB leds[NUM_LEDS];

inline uint8_t add_clipped( uint16_t left, uint16_t right)
{
	uint16_t result = left + right;
	if (result > 255) result = 255;
	return result;
}

inline void add_clipped( CRGB &left, const CRGB &right)
{
	left = CRGB(
			add_clipped(left.red, right.red),
			add_clipped( left.green, right.green),
			add_clipped( left.blue, right.blue)
			);
}


#include <string.h> // for memset

/// flame color pattern. This pattern is twice as big as the pattern that is actually drawn to allow
/// anti-aliasing when rendering.
const CRGB pattern[] = {
		CRGB( 20, 0, 0), 	CRGB( 50, 0, 0),
		CRGB( 80, 0, 0), 	CRGB( 100, 20, 0),
		CRGB( 120, 40, 0), 	CRGB( 120, 60, 5),
		CRGB( 120, 80, 10), 	CRGB( 170, 110, 20),
		CRGB( 240, 140, 30), CRGB( 170, 110, 20),
		CRGB( 120, 80, 10), 	CRGB( 120, 60, 5),
		CRGB( 120, 40, 0), 	CRGB( 100, 20, 0),
		CRGB( 80, 0, 0), 	CRGB( 50, 0, 0),
		CRGB( 20, 0, 0),
};
const uint8_t pattern_size = sizeof pattern/sizeof pattern[0];

/// A flame renders a flame-colored pattern on a sequence of leds.
/// At each step of the animation, the flame will make a move to the left or
/// right at random.
/// A flame will remember its position. Note that the position is stored as
/// a 15.1 fixed point number and that the used color sequence is also twice as
/// big as the sequence that is actually drawn. This is done to create a smoother
/// animation.
class flame
{
public:
	explicit flame( uint16_t position = 0)
	:position( position * 2){}

	void step( CRGB *leds, uint16_t size)
	{
		if ((rand()&1) && position > 0)
		{
			position--;
		}
		if ((rand()&1) && ((position + pattern_size) < size*2))
		{
			position++;
		}

		draw( leds, size);
	}

private:
	uint16_t position;

	/// Draw the color sequence at this flames position.
	void draw(CRGB* leds, uint16_t size)
	{
		for (uint8_t color = 0; color < sizeof pattern / sizeof pattern[0];
				++color)
		{
			// note that we're only using half of the sequence colors
			if (!((position + color)&1) && (position + color)/2 < size)
			{
				add_clipped( leds[(position + color)/2], pattern[color]);
			}
		}
	}
};

/// Animate a campfire on a WS2811 led string.
/// This function creates a fixed amount of flame objects, disperses
/// them over the led string and then lets the flames do their animation in
/// a infinite loop.
template< uint16_t size>
void campfire( CRGB (&leds)[size], uint8_t channel)
{
	static const uint8_t flamecount = 10;
	flame flames[flamecount];
	const uint16_t step = (size - pattern_size)/flamecount;
	for (uint16_t pos = 0; pos < flamecount; ++pos)
	{
		flames[pos] = flame( step*pos);
	}
	for(;;)
	{
		memset( leds, 0, sizeof leds);
		for (uint8_t f = 0; f < flamecount; ++f)
		{
			flames[f].step( leds, size);
		}
//		_delay_ms(20);
		FastLED.show();
	}
}


void setup() {
	CRGB leds[NUM_LEDS];

	FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

	// set master brightness control
	FastLED.setBrightness(200);

	campfire(leds, 13);
}

void loop() {

}



#endif
