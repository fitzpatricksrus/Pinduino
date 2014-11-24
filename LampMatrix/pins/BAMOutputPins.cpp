/*
 * BAMOutputPins.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "BAMOutputPins.h"

#include "../scheduler/Timer.h"
#include "../Tests/Debug.h"

static const byte mask[] = { 0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000 };
static byte valueMap[256];

BAMOutputPins::BAMOutputPins(scheduler::Timer* timerIn, OutputPins* pinsIn)
: AnalogOutputPins(), pins(pinsIn), values(0), bitInCycle(0), timer(timerIn)
{
	values = new byte[pins->getPinCount()];
	for (byte i = 0; i < pins->getPinCount(); i++) {
		values[i] = 0;
	}
#ifdef USE_MODULATED_VALUES
	for (byte i = 0; i < 8; i++) {
		modulatedValues[i] = new bool[pins->getPinCount()];
	}
	buildModulationValues();
#endif
}

BAMOutputPins::~BAMOutputPins() {
	delete[] values;
#ifdef USE_MODULATED_VALUES
	for (byte i = 0; i < 8; i++) {
		delete[] modulatedValues[i];
	}
#endif
}

byte BAMOutputPins::getPinCount() const {
	return pins->getPinCount();
}

byte BAMOutputPins::getPin(byte pinNdx) const {
	return values[pinNdx];
}

void BAMOutputPins::setPin(byte pinNdx, byte pinValue) {
	values[pinNdx] = pinValue;
}

void BAMOutputPins::latch() {
#ifdef USE_MODULATED_VALUES
	buildModulationValues();
#endif
}

void BAMOutputPins::setEnabled(bool on) {
	if (on) {
		timer->addCallback(this);
	} else {
		timer->removeCallback(this);
	}
}

void BAMOutputPins::setup() {
	//reset the timer
	bitInCycle = 0;
	for (int i = 0; i < pins->getPinCount(); i++) {
		values[i] = 0;
		pins->setPin(i, 0);
	}
	for (int i = 0; i < 256; i++) {
		valueMap[i] = i;
/*		if (i > 128) {
    		valueMap[i] = map(i, 128, 256, 64, 256);
    	} else if (i > 16){
    		valueMap[i] = map(i, 16, 128, 8, 64);
    	} else {
    		valueMap[i] = map(i, 0, 16, 0, 8);
    	} */
	}
}

void BAMOutputPins::loop() {
#ifdef USE_MODULATED_VALUES
	for (int i = 0; i < pins->getPinCount(); i++) {
		pins->setPin(i, modulatedValues[bitInCycle][i]);
	}
#else
	for (int i = 0; i < pins->getPinCount(); i++) {
		byte value = values[i];
		value = valueMap[value];
		bool isOn = ((value & mask[bitInCycle]) != 0);
		pins->setPin(i, isOn);
	}
#endif
	pins->latch();
	unsigned int rval = mask[bitInCycle];
	bitInCycle = (bitInCycle + 1) & 0b00000111;
	timer->setTicks(rval);
}

#ifdef USE_MODULATED_VALUES
void BAMOutputPins::buildModulationValues() {
	// this routine precalculates which pins are on for each
	// bit in a complete cycle.
	for (byte cycle = 0; cycle < 8; cycle++) {
		for (byte pin = 0; pin < pins->getPinCount(); pin++) {
	    	byte value = values[pin];
	    	value = valueMap[value];
	        bool isOn = ((value & mask[cycle]) != 0);
	        modulatedValues[cycle][pin] = isOn;
		}
	}
}
#endif
