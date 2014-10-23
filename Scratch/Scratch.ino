// #include "FlexiTimer2.h"

// #include "MatrixColumnPattern.h"

//#define RUN_MatrixPinsTest

#include <Arduino.h>

#include "Tests/Debug.h"
#include "DirectOutputPins.h"

static byte pinsNums[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
static DirectOutputPins pins(8, pinsNums);


void setup() {
	Serial.begin(57200);
	pins.initPins();
}

static const long mask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };
static long values[] = { B00000001,B0000100,B00000111,B0001000,B0001111,B0010000,B0001111,B00000000 };


uint32_t cycleCount = 0;
uint8_t bitInCycle = 0;
uint32_t lastCycle = 0;
uint32_t cycleDelay = 0;

uint32_t lastTime = 0;
byte lastCount = 0;
void loop() {

	if (micros() - lastCycle > cycleDelay) {
		for (int i = 0; i < 8; i++) {
			pins.setPin(i, (values[i] & mask[cycleCount]) != 0);
		}
		pins.latch();

		cycleCount = (cycleCount + 1) & 0x07;
		lastCycle = micros();
		cycleDelay = mask[cycleCount] << 4;
	}

	if (millis() - lastTime > 250) {
		for (int i = 0; i < 8; i++) {
			values[i] = lastCount % 256;
		}
		lastCount = (lastCount + 1) % 256;
		lastTime = millis();
	}
}


