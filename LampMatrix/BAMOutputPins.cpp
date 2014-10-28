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

void BAMOutputPins::setup() {
	//reset the timer
	bitInCycle = 0;
	for (int i = 0; i < 8; i++) {
		values[i] = 0;
		pins->setPin(i, 0);
	}
}

void BAMOutputPins::loop() {
	bitInCycle = (bitInCycle + 1) & 0b00000111;
    for (int i = 0; i < 8; i++) {
        bool isOn = ((values[i] & mask[bitInCycle]) != 0);
    	pins->setPin(i, isOn);
    }
    pins->latch();
    unsigned long rval = mask[bitInCycle];
    timer->setTicks(rval << 5);
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

