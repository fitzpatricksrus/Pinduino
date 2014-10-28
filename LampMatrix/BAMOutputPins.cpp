/*
 * BAMOutputPins.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "BAMOutputPins.h"

#include "scheduler/Timer.h"
#include "Tests/Debug.h"

static const byte mask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };
static byte valueMap[256];

void BAMOutputPins::setup() {
	//reset the timer
	bitInCycle = 0;
	for (int i = 0; i < 8; i++) {
		values[i] = 0;
		pins->setPin(i, 0);
	}
	for (int i = 0; i < 256; i++) {
		valueMap[i] = i;
		if (i > 128) {
    		valueMap[i] = map(i, 128, 256, 92, 256);
    	} else if (i > 32){
    		valueMap[i] = map(i, 32, 128, 16, 92);
    	} else {
    		valueMap[i] = map(i, 0, 32, 0, 16);
    	}
	}
}

void BAMOutputPins::loop() {
	bitInCycle = (bitInCycle + 1) & 0b00000111;
    for (int i = 0; i < 8; i++) {
    	byte value = values[i];
    	value = valueMap[value];
        bool isOn = ((value & mask[bitInCycle]) != 0);
    	pins->setPin(i, isOn);
    }
    pins->latch();
    unsigned long rval = mask[bitInCycle];
    timer->setTicks(rval << 6);
}

BAMOutputPins::BAMOutputPins(scheduler::Timer* timerIn, OutputPins* pinsIn)
: AnalogOutputPins(), pins(pinsIn), values(0), bitInCycle(0), timer(timerIn)
{
	values = new byte[pins->getPinCount()];
}

BAMOutputPins::~BAMOutputPins() {
	delete[] values;
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
	timer->addCallback(this, scheduler::Timer::PS64, mask[0]);
}

