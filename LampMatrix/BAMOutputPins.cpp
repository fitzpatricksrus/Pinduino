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
static const int delayTime[] = { B00000001 << 8,B00000010 << 8,B00000100 << 8,B00001000 << 8,B00010000 << 8,B00100000 << 8,B01000000 << 8,B10000000 << 8 };

void BAMOutputPins::setup() {
	//reset the timer
	bitInCycle = 0;
	cyclesOn = 0;
	cycleCount = 0;
}

void BAMOutputPins::loop() {
	cycleCount++;
	bool pinsOn = false;
	for (int i = pins->getPinCount() - 1; i >= 0; i--) {
		bool valueBitIsSet = (values[i] & valueMask[bitInCycle]) !=0;
		pins->setPin(i, valueBitIsSet);
		pinsOn = pinsOn || valueBitIsSet;
	}
	cyclesOn += (pinsOn) ? delayTime[bitInCycle] : 0;
	pins->latch();
	scheduler::Timer::TIMER1.setTicks(valueMask[bitInCycle]);

	bitInCycle = (bitInCycle + 1) & B0000111;
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
	scheduler::Timer::TIMER1.addCallback(this, scheduler::Timer::PS64, delayTime[0]);
}

