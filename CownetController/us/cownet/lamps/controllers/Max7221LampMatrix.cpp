/*
 * Max7221LampMatrix.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: jfitzpatrick
 */

#include "Max7221LampMatrix.h"

#include "../../timers/TimerUtil.h"
#include <Debug.h>

namespace us_cownet_lamps_controllers {

using us_cownet_timers::TimerUtil;

Max7221LampMatrix::Max7221LampMatrix()
: refreshFrequency(0), pattern(NULL), tockCallback(this, &Max7221LampMatrix::tock), max7221(10)
{
	pinMode(51, OUTPUT);
	pinMode(52, OUTPUT);
	pinMode(53, OUTPUT);
}

Max7221LampMatrix::Max7221LampMatrix(long refreshFrequencyIn, int selectPin)
: refreshFrequency(refreshFrequencyIn), pattern(NULL), tockCallback(this, &Max7221LampMatrix::tock), max7221(selectPin)
{
}

Max7221LampMatrix::~Max7221LampMatrix() {
}

LampPattern* Max7221LampMatrix::getPattern() {
	return pattern;
}

void Max7221LampMatrix::setPattern(LampPattern* newPattern) {
	// if nothing has changed, don't do anything
	if (pattern == newPattern) return;

	if (pattern != NULL) {	// we have a new pattern, detach the old one.
		if (newPattern == NULL) {
			// turn off timer
			TimerUtil::INSTANCE.detachCallback(&tockCallback);
			// turn off matrix
			max7221.setEnabled(false);
			Serial.println("Max7221LampMatrix::setPattern detaching from timer");
		}
		pattern->detached();
	}

	LampPattern* oldPattern = pattern;
	pattern = newPattern;

	if (pattern != NULL) {
		pattern->attached();
		if (oldPattern == NULL) {
			// turn on matrix
			max7221.init();
			// turn on timer
			Serial.println("Max7221LampMatrix::setPattern attaching to timer");
			TimerUtil::INSTANCE.attachTickerCallback(&tockCallback, refreshFrequency);
		}
	}
}

void Max7221LampMatrix::tock() {
	//refresh the lamp matrix
	Serial << "Time: " << TimerUtil::INSTANCE.currentTicks() << endl;
	int colCount = pattern->getColCount();
	for (int i = 0; i < colCount; i++) {
		Serial << "col=" << "  " << i << "  " << _BIN(pattern->getColumn(i)) << endl;
		max7221.setColumn(i, pattern->getColumn(i));
	}

	Serial.println();
	pattern->endOfMatrixSync();
	notifyListenersOfSync();
}

} /* namespace us_cownet_lamps_tests */
