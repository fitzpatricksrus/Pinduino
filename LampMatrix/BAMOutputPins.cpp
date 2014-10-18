/*
 * BAMOutputPins.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "BAMOutputPins.h"

#include "scheduler/Timer.h"

static const byte valueMask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };

void BAMOutputPins::setup() {
	//reset the timer

}

void BAMOutputPins::run() {
	//latch the pins
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
	if (scheduler::Timer::TIMER1.getCallback() != this) {
		// if this set of pins wasn't latch, make it the active pins
		scheduler::Timer::TIMER1.setCallback(this, scheduler::Timer::PS64, 256 << bitInCycle);
	}

	for (int i = pins->getPinCount() - 1; i >= 0; i--) {
		pins->setPin(i, (values[i] & valueMask[bitInCycle]) !=0);
	}
	scheduler::Timer::TIMER1.setTicks(256 << bitInCycle);

	bitInCycle = (bitInCycle + 1) & 0x07;
}

