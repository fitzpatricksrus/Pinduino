#include <Arduino.h>
#include "BitVector.h"

static int COLUMN_COUNT = 8;

class LampData {
public:
	int lampCount;
	byte *data;
};

static int pins[] = { 22,23,24,25, 26,27,28,29, 34,35,36,37, 38,39,40,41 };
static enum {
    DATA0,
    DATA1,
    DATA2,
    DATA3,
    DATA4,
    DATA5,
    DATA6,
    DATA7,
    DATA8,      //A0
    DATA9,      //A1
    DATA10,     //A2
    DATA11,     //A3
    DATA12,     //A4
    DATA13,     //A5
} SIGNAL;

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

static void writeColumn(byte values, int column) {
    // update rows
	BitVector v(values);
	for (int i = 0; i < COLUMN_COUNT; i++) {
	    if (v[i]) {
	        on(i);
	    } else {
	        off(i);
	    }
	}
}

static void refresh(LampData& lampData) {
	for (int i = 0; i < lampData.lampCount; i++) {
		writeColumn(lampData.data[i], i % COLUMN_COUNT);
	}
}

static byte rawData[] = {
    0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F,
	0x0F
};

static LampData lampData;

void setupXX() {
	for (int i = 0; i < 16; i++) {
		pinMode(pins[i], OUTPUT);
		on(i);
	}

	lampData.lampCount = 15;
	lampData.data = &rawData[0];
}

void loopXX() {
//    while (true) {
//   	refreshOnePWMCycle();
//    }
}

