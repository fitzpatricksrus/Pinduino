/*
 * RGBTest4.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: Dad
 */

#include "RGB4Test.h"

//#define WPC
//#define MAX7221


#include <Arduino.h>
//#include <DueTimer.h>
#include "BitVector.h"
#ifdef MAX7221
#include <Max7221.h>
#endif

static const int COLUMN_SIZE = 8;

static int pinCount = 16;
static int pins[] = { 22,23,24,25, 26,27,28,29, 34,35,36,37, 38,39,40,41 };
typedef enum {
	DATA0,
	DATA1,
	DATA2,
	DATA3,
	DATA4,
	DATA5,
	DATA6,
	DATA7,
	CONTROL_ROWS, //CONTROL0,
	CONTROL_COLUMNS, //CONTROL1,
	CONTROL2,
	CONTROL3,
	CONTROL4,
	CONTROL5,
	CONTROL6,
	CONTROL7,
} Signal;

static inline void pinLow(int pin) {
    digitalWrite(pin, LOW);
}

static inline void pinHigh(int pin) {
    digitalWrite(pin, HIGH);
}

static inline void pinOn(int pin) {
    pinHigh(pin);
}

static inline void pinOff(int pin) {
    pinLow(pin);
}

static inline void on(int pin) {
    pinOn(pins[pin]);
}

static inline void off(int pin) {
    pinOff(pins[pin]);
}

static inline void signal(int ndx) {
    pinOn(pins[ndx]);
    pinOff(pins[ndx]);
}

/*
128 = 1/2   128
 64 = 1/4    64
 32 = 1/8    32
 16 = 1/16   16
  8 = 1/32    8
  4 = 1/64    4
  2 = 1/128   2
  1 = 1/256   1
	*/

static int greyIndex8[] = {
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x04,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x02,

		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x04,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x01,

		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x04,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x02,

		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x04,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x08,
		0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80, 0x10,  0x80, 0x40, 0x80, 0x20,  0x80, 0x40, 0x80	//, 0x00,
};

static int gryIndex7[] = {	// 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x04,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x02,

		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x04,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x01,

		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x04,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x02,

		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x04,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40, 0x08,
		0x40, 0x20, 0x40, 0x10,  0x40, 0x20, 0x40	//, 0x00,
};

static int greyIndex6[] = { // 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20, 0x04,
		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20, 0x02,
		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20, 0x04,
		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20, 0x01,

		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20, 0x04,
		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20, 0x02,
		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20, 0x04,
		0x20, 0x10, 0x20, 0x08,  0x20, 0x10, 0x20	//, 0x00,
};

static int greyIndex5[] = { // 0x10, 0x08, 0x04, 0x02, 0x01
		0x10, 0x08, 0x10, 0x04,  0x10, 0x08, 0x10, 0x02,
		0x10, 0x08, 0x10, 0x04,  0x10, 0x08, 0x10, 0x01,
		0x10, 0x08, 0x10, 0x04,  0x10, 0x08, 0x10, 0x02,
		0x10, 0x08, 0x10, 0x04,  0x10, 0x08, 0x10 //, 0x00,
};

static int greyIndex4[] = {	// 0x08, 0x40, 0x02, 0x01
		0x88, 0x44, 0x88, 0x22,
		0x88, 0x44, 0x88, 0x11,
		0x88, 0x44, 0x88, 0x22,
		0x88, 0x44, 0x88, // 0x00,
};

static int greyIndex3[] = { // 0x04, 0x02, 0x01
		0x44, 0x22, 0x44, 0x11,
		0x44, 0x22, 0x44, // 0x00,
};

static int greyIndex2[] = { // 0x02, 0x01
		0b10101010, 0b01010101,
		0b10101010, // 0xb00000000,
};

static int greyIndex1[] = { //  0x01
		0b11111111, // 0xb00000000,
};

#ifdef MAX7221
static Max7221 max7221(9);

#endif

RGBTest4::RGBTest4(byte* dataIn, int dataSizeIn)
: cyclePosition(0), columnPosition(0), data(dataIn), dataSize(dataSizeIn)
{
#ifdef MAX7221
	max7221.init();
#else
	for (int i = 0; i < pinCount; i++) {
		pinMode(pins[i], OUTPUT);
	}
#endif
}

RGBTest4::~RGBTest4() {

}

void RGBTest4::refreshOneRGBColumn(int col, bool* values) {
#ifdef MAX7221
#else
	for (int i = 0; i < COLUMN_SIZE; i++) {
		if (values[i]) {
			on(i);
		} else {
			off(i);
		}
	}
#endif
}


void RGBTest4::setup() {
	cyclePosition = 0;
	columnPosition = 0;
//	Serial.begin(57600);
}

void RGBTest4::loop() {
	bool values[COLUMN_SIZE];

//	Serial.print(columnPosition);
//	Serial.print("  ");
//	Serial.print(cyclePosition);
//	Serial.print("  ");
	for (int i = 0; i < COLUMN_SIZE; i++) {
		values[i] = data[columnPosition+i] & greyIndex8[cyclePosition];
//		Serial.print(values[i] ? "1" : "0");
	}
//	Serial.println();
	refreshOneRGBColumn(columnPosition / COLUMN_SIZE, values);
	columnPosition = columnPosition + COLUMN_SIZE;
	if (columnPosition >= dataSize) {
		cyclePosition = (cyclePosition + 1) % 255;
		columnPosition = 0;
	}
}
