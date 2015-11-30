/*
 * DebugLampMatrix.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: Dad
 */

#include "DebugLampMatrix.h"
#include "../../timers/TimerUtil.h"
#include <Debug.h>

namespace us_cownet_lamps_controllers {

using us_cownet_timers::TimerUtil;

DebugLampMatrix::DebugLampMatrix(long refreshFrequencyIn)
: refreshFrequency(refreshFrequencyIn), pattern(NULL), tockCallback(this, &DebugLampMatrix::tock)
{
}

DebugLampMatrix::~DebugLampMatrix() {
}

LampPattern* DebugLampMatrix::getPattern() {
	return pattern;
}

void DebugLampMatrix::setPattern(LampPattern* newPattern) {
	// if nothing has changed, don't do anything
	if (pattern == newPattern) return;

	if (pattern != NULL) {	// we have a new pattern, detach the old one.
		if (newPattern == NULL) {
			// turn off timer
			TimerUtil::INSTANCE.detachCallback(&tockCallback);
			// turn off matrix
		}
		pattern->detached();
	}

	LampPattern* oldPattern = pattern;
	pattern = newPattern;

	if (pattern != NULL) {
		pattern->attached();
		if (oldPattern == NULL) {
			// turn on matrix
			// turn on timer
			TimerUtil::INSTANCE.attachTickerCallback(&tockCallback, refreshFrequency);
		}
	}
}

void DebugLampMatrix::tock() {
	int colCount = pattern->getLampBankCount();
	for (int i = 0; i < colCount; i++) {
//		Serial << _BIN(pattern->getColumn(i)) << endl;
		Serial.print(pattern->getLampBank(i));
	}

	Serial.println(".");
	pattern->endOfMatrixSync();
	notifyListenersOfSync();
}

} /* namespace us_cownet_lamps_controllers */
