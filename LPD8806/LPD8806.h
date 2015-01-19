#ifndef __LDP8806__
#define __LDP8806__

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class LPD8806 {
public:
	LPD8806(uint16_t n, uint8_t dpin, uint8_t cpin); // Configurable pins
	LPD8806(uint16_t n); // Use SPI hardware; specific pins only
	LPD8806(void); // Empty constructor; init pins & strip length later
	void begin(void);
	void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
	void setPixelColor(uint16_t n, uint32_t c);
	void show(void);
	void updatePins(uint8_t dpin, uint8_t cpin); // Change pins, configurable
	void updatePins(void);                       // Change pins, hardware SPI
	void updateLength(uint16_t n);               // Change strip length
	uint16_t numPixels(void);
	uint32_t Color(byte, byte, byte);
	uint32_t getPixelColor(uint16_t n);

private:
	uint16_t numLEDs;    // Number of RGB LEDs in strip
	uint16_t numBytes;   // Size of 'pixels' buffer below
	uint8_t *pixels;     // Holds LED color values (3 bytes each) + latch bytes
	uint8_t clkpin;      // Clock pin number
	uint8_t datapin;     // data pin number
#ifdef __AVR__
	uint8_t clkpinmask;
	uint8_t datapinmask; // Clock & data PORT bitmasks
	volatile uint8_t *clkport;
	volatile uint8_t *dataport;   // Clock & data PORT registers
#endif
	void startBitbang(void);
	void startSPI(void);
	boolean hardwareSPI; // If 'true', using hardware SPI
	boolean begun;       // If 'true', begin() method was previously invoked
};

#endif
