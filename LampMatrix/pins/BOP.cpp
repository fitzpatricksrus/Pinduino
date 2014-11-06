/*
 * BOP.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Dad
 */

#include "BOP.h"

#include "../scheduler/Timer.h"
#include "../Tests/Debug.h"

static byte valueMap[256];

BOP::BOP(scheduler::Timer* timerIn, OutputPins* pinsIn)
: AnalogOutputPins(), pins(pinsIn), values(0), timer(timerIn), BAM(timerIn, this)
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

BOP::~BOP() {
	delete[] values;
#ifdef USE_MODULATED_VALUES
	for (byte i = 0; i < 8; i++) {
		delete[] modulatedValues[i];
	}
#endif
}

byte BOP::getPinCount() const {
	return pins->getPinCount();
}

byte BOP::getPin(byte pinNdx) const {
	return values[pinNdx];
}

void BOP::setPin(byte pinNdx, byte pinValue) {
	values[pinNdx] = pinValue;
}

void BOP::latch() {
#ifdef USE_MODULATED_VALUES
	buildModulationValues();
#endif
}

void BOP::setEnabled(bool on) {
	if (on) {
		for (int i = 0; i < pins->getPinCount(); i++) {
			values[i] = 0;
			pins->setPin(i, 0);
		}
		for (int i = 0; i < 256; i++) {
			valueMap[i] = i;
			if (i > 128) {
	    		valueMap[i] = map(i, 128, 256, 64, 256);
	    	} else if (i > 16){
	    		valueMap[i] = map(i, 16, 128, 8, 64);
	    	} else {
	    		valueMap[i] = map(i, 0, 16, 0, 8);
	    	}
		}
		BAM.enableCallbacks();
	} else {
		BAM.disableCallbacks();
	}
}

void BOP::loop(byte bit, byte mask) {
#ifdef USE_MODULATED_VALUES
	for (int i = 0; i < pins->getPinCount(); i++) {
		pins->setPin(i, modulatedValues[bit][i]);
	}
#else
	for (int i = 0; i < pins->getPinCount(); i++) {
		byte value = values[i];
		value = valueMap[value];
		bool isOn = ((value & mask) != 0);
		pins->setPin(i, isOn);
	}
#endif
	pins->latch();
}

#ifdef USE_MODULATED_VALUES
void BOP::buildModulationValues() {
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
