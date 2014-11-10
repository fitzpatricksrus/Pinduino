/*
 * SimpleMatrixPins.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#include "SimpleMatrixPins.h"

namespace pins {

SimpleMatrixPins::SimpleMatrixPins(scheduler::Timer* timerIn, OutputPins* pinsIn)
: timer(timerIn), pattern(0), currentColumn(0), pins(pinsIn)
{
}

SimpleMatrixPins::~SimpleMatrixPins() {
}

void SimpleMatrixPins::initPins() {
	currentColumn = 0;
	for (byte i = 0; i < pattern->getColCount(); i++) {
		pins[i].initPins();
	}
	timer->addCallback(this);
	timer->enableCallbacks();
}

void SimpleMatrixPins::setPattern(MatrixPattern* patternIn) {
	pattern = patternIn;
}

void SimpleMatrixPins::latch() {
	// latch in the current row.
	for (byte i = 0; i < pattern->getColCount(); i++) {
//		pins[currentColumn].setPinPattern();
	}
}

void SimpleMatrixPins::setup() {
}

void SimpleMatrixPins::loop() {
	latch();
	currentColumn++;
	if (currentColumn > pattern->getColCount()) {
		currentColumn = 0;
	}
}

} /* namespace pins */
