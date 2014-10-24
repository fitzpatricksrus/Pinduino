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

static const int mask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };
static int values[] = { B00000001,B0000100,B00000111,B0001000,B0001111,B0010000,B0001111,B00000000 };

unsigned int lastCycle = 0;
unsigned int cycleDelay = 0;
byte partOfCycle = 0;
int processCycle(int value) {
    partOfCycle = (partOfCycle + 1) & 0x07;
    cycleDelay = mask[partOfCycle];
    bool isOn = ((value & mask[partOfCycle]) != 0);
    for (int i = 0; i < 8; i++) pins.setPin(i, isOn);
    pins.latch();
    return mask[partOfCycle];
}

unsigned long lastTime = 0;
int value = 0;
void loop() {
	if (micros() - lastCycle > cycleDelay) {
		cycleDelay = processCycle(value);
		lastCycle = micros();
	}

	if ((millis() - lastTime) > 1000) {
		value = (value + 1) % 256;
		lastTime = millis();
		Serial << value << "  " << millis() << "  " << lastTime << endl;
	}

}


