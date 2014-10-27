// #include "FlexiTimer2.h"

// #include "MatrixColumnPattern.h"

//#define RUN_MatrixPinsTest

#include <Arduino.h>

#include "Tests/Debug.h"
#include "DirectOutputPins.h"
#include "SPIOutputPins.h"
#include "SPI.h"
#include "LedControl.h"
#include "Timer.h"
#include "BC.h"


static byte pinsNums[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
static DirectOutputPins pins(8, pinsNums);
static SPIOutputPins spins(8);
static byte SLAVE_PIN = 10;

unsigned long lastTime = 0;
int value = 0;
long count = 0;

void BAMSetup() {
	Serial.begin(57200);
	pins.initPins();
	spins.slaveSelectPin(SLAVE_PIN);
	spins.initPins();
}

static const int mask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };

unsigned long lastCycle = 0;
unsigned long cycleDelay = 0;
byte partOfCycle = 0;
unsigned long processCycle(int value) {
    partOfCycle = (partOfCycle + 1) & 0b00000111;
    bool isOn = ((value & mask[partOfCycle]) != 0);
    for (int i = 0; i < 8; i++) {
    	pins.setPin(i, isOn);
    	spins.setPin(i, isOn);
    }
    pins.latch();
    spins.latch();
    unsigned long rval = mask[partOfCycle];
    return rval << 6;
}

void BAMLoop() {
	count++;
	if (micros() - lastCycle > cycleDelay) {
		cycleDelay = processCycle(value);
//		Serial << cycleDelay << endl;
		lastCycle = micros();
	}

	if ((millis() - lastTime) > 10) {
		value = (value + 1) % 0xFF;
		if (value == 0) value = 1;
//		Serial << value << "  " << millis() << "  " << lastTime << "   " << "  "<< count << endl;
		lastTime = millis();
		count = 0;
	}
}


static Tests::DebugCounter cnt;
static TimerCallback callback;

void setup() {
//	BAMSetup();
	BC::doSetup();
	Timer::timer1.init();
	Timer::timer1.addCallback(&callback, Timer::PS1024, 256);
	Timer::timer1.enableCallbacks();
}

void loop() {
//	BAMLoop();
	BC::doLoop();
	cnt.ping();
	if (cnt) {
		Serial << "Total: " << cnt <<  endl;
	}
	if (callback.timerCnt) {
		Serial << "timer: " << callback.timerCnt << endl;
	}
}
