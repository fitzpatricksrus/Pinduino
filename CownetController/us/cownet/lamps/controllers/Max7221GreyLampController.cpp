/*
 * Max7221GreyLampController.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: Dad
 */

#include "Max7221GreyLampController.h"

#include "../../timers/TimerUtil.h"
using us_cownet_timers::TimerUtil;

namespace us_cownet_lamps_controllers {

static bool phaseMaskNeedsToBeBuilt = true;
static byte phaseMask[256];

Max7221GreyLampController::Max7221GreyLampController(int selectPin, long refreshFrequencyIn)
: max7221(selectPin), pattern(NULL), refreshFrequency(refreshFrequencyIn),
  tockCallback(this, &Max7221GreyLampController::tock), lampPhase(0) {

	if (phaseMaskNeedsToBeBuilt) {
		int ndx = 0;
		phaseMask[ndx++] = 0;
		for (int maskBit = 1; maskBit < 8; maskBit++) {
			byte repeateCount = 1 << (maskBit - 1);
			for (int i = 0; i < repeateCount; i++) {
				phaseMask[ndx++] = repeateCount;
			}
		}
		phaseMaskNeedsToBeBuilt = false;
	}

}

Max7221GreyLampController::~Max7221GreyLampController() {
}

void Max7221GreyLampController::setPattern(UniversalLampPattern* newPattern) {
	// if nothing has changed, don't do anything
	if (pattern == newPattern) return;

	if (pattern != NULL) {	// we have a new pattern, detach the old one.
		if (newPattern == NULL) {
			// turn off timer
			TimerUtil::INSTANCE.detachCallback(&tockCallback);
			// turn off matrix
			max7221.setEnabled(false);
//			Serial.println("Max7221LampMatrix::setPattern detaching from timer");
		}
//		pattern->detached();
	}

	UniversalLampPattern* oldPattern = pattern;
	pattern = newPattern;

	if (pattern != NULL) {
//		pattern->attached();
		if (oldPattern == NULL) {
			// turn on matrix
			max7221.init();
			// turn on timer
			TimerUtil::INSTANCE.attachTickerCallback(&tockCallback, refreshFrequency);
		}
	}
}

void Max7221GreyLampController::tock() {
	byte result = 0;
//	int bankBase = bankIndex << 3;
	for (int i = 7; i >= 0; i--) {
		result <<= 1;
//		if (getLamp(bankBase + i)) {
//			result |= 1;
//		}
	}



	//refresh the lamp matrix
	int colCount = pattern->getLampBankCount();
	for (int i = 0; i < colCount; i++) {
		max7221.setColumn(i, pattern->getLampBank(i));
	}

//	pattern->endOfMatrixSync();
//	notifyListenersOfSync();
}

} /* namespace us_cownet_lamps_controllers */
