/*
 * BC.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: Dad
 */

#include "BC.h"
#include <Arduino.h>

#include "Tests/Debug.h"
#include "DirectOutputPins.h"
#include "SPIOutputPins.h"
#include "SPI.h"
#include "LedControl.h"
#include "Timer.h"

#define looped

static byte pinsNums[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
static DirectOutputPins pins(8, pinsNums);
static SPIOutputPins spins(8);
static byte SLAVE_PIN = 10;

static unsigned long lastTime = 0;
static int value = 0;
static long count = 0;
static BC callback;

void BC::doSetup() {
	Serial.begin(57200);
	pins.initPins();
	spins.slaveSelectPin(SLAVE_PIN);
	spins.initPins();
#ifndef looped
	Timer::timer1.addCallback(&callback, Timer::PS256, 1);
#endif
}

static const int mask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };

static byte partOfCycle = 0;
static unsigned long processCycle(int value) {
    partOfCycle = (partOfCycle + 1) & 0b00000111;
    bool isOn = ((value & mask[partOfCycle]) != 0);
    for (int i = 0; i < 8; i++) {
    	pins.setPin(i, isOn);
    	spins.setPin(i, isOn);
    }
    pins.latch();
    spins.latch();
    unsigned long rval = mask[partOfCycle];
#ifdef looped
    return rval << 5;
#else
    return rval;
#endif
}

static unsigned long lastCycle = 0;
static unsigned long cycleDelay = 0;

void BC::doLoop() {
	count++;
#ifdef looped
	if (micros() - lastCycle > cycleDelay) {
		cycleDelay = processCycle(((value) < 256) ? value : 512 - value);
//		Serial << cycleDelay << endl;
		lastCycle = micros();
	}
#endif

	if ((millis() - lastTime) > 10) {
		value = (value + 1) % 0x1FF;
		if (value == 0) value = 1;
//		Serial << value << "  " << millis() << "  " << lastTime << "   " << "  "<< count << endl;
		lastTime = millis();
		count = 0;
	}
}

void BC::setup() {
}

void BC::loop() {
#ifndef looped
	unsigned long cycleDelay = processCycle(value);
	Timer::timer1.setTicks(cycleDelay << 4);
#endif
}
