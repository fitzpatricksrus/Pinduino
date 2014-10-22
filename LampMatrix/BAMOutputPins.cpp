/*
 * BAMOutputPins.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "BAMOutputPins.h"

#include "scheduler/Timer.h"
#include "Tests/Debug.h"

static const byte valueMask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };

#define bitMultiplier 1

void BAMOutputPins::setup() {
	//reset the timer
	bitInCycle = 0;
}

void BAMOutputPins::loop() {
	for (int i = pins->getPinCount() - 1; i >= 0; i--) {
		pins->setPin(i, (values[i] & valueMask[bitInCycle]) !=0);
	}
	pins->latch();
	scheduler::Timer::TIMER1.setTicks(valueMask[bitInCycle] << bitMultiplier);

	bitInCycle = (bitInCycle + 1) & 0x07;
}

BAMOutputPins::BAMOutputPins(OutputPins* pinsIn)
: AnalogOutputPins(), pins(pinsIn), values(0), bitInCycle(0)
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
	scheduler::Timer::TIMER1.addCallback(this, scheduler::Timer::PS8, valueMask[0] << bitMultiplier);
}

