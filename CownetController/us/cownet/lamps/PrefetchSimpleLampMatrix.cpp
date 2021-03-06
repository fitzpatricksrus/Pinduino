/*
 * PrefetchSimpleLampMatrix.cpp
 *
 *  Created on: Oct 22, 2015
 *      Author: jfitzpatrick
 */

#include "PrefetchSimpleLampMatrix.h"

namespace us_cownet_lamps {

PrefetchSimpleLampMatrix::PrefetchSimpleLampMatrix(PinballOutputController* controllerIn, long ticksIn)
: controller(controllerIn), ticks(ticksIn), currentColumn(0), nextPattern(NULL), attachedPattern(NULL),
  syncCallback(NULL), thisCallback(this, &PrefetchSimpleLampMatrix::tock), prefetchedColumnValue(0)
{
}

PrefetchSimpleLampMatrix::~PrefetchSimpleLampMatrix() {
}

LampPattern* PrefetchSimpleLampMatrix::getDisplayedPattern() {
	return attachedPattern;
}

LampPattern* PrefetchSimpleLampMatrix::getPattern() {
	return nextPattern;
}

void PrefetchSimpleLampMatrix::setPattern(LampPattern* lamps) {
	if (attachedPattern == NULL && lamps != NULL) {
		// kick start the first refresh.
		internalSetPattern(lamps);
		nextPattern = lamps;
		TimerUtil::INSTANCE.attachTickerCallback(&thisCallback, ticks);
	} else {
		// transitioning from one pattern to another is done in tock()
		// tock() also terminates refresh if we're setting to null.
		nextPattern = lamps;
	}
}

void PrefetchSimpleLampMatrix::tock() {
	// turn off all columns for a split second so when we change to a new
	// column we don't get artifacts from the previous one.
	controller->writeCol((byte)0);
	// update the rows that will light when we turn a column on
	controller->writeRow(prefetchedColumnValue);
	// turn on the proper column
	controller->writeCol((byte)(1 << currentColumn));
	// calculate the next column to light
	currentColumn = (currentColumn + 1) % attachedPattern->getLampBankCount();
	if (currentColumn == 0) {
		// we've finished refreshing the matrix one complete cycle.
		if (syncCallback != NULL) {
			syncCallback->call();
		}
		internalEndOfMatrixSync(attachedPattern);
		// transition from one pattern to next on sync
		internalSetPattern(nextPattern);
		if (attachedPattern == NULL) {	//note currentPattern == nextPattern here
			TimerUtil::INSTANCE.detachCallback(&thisCallback);
		}
	}
	prefetchedColumnValue = internalGetColumn(attachedPattern, currentColumn);
}

void PrefetchSimpleLampMatrix::setSyncCallback(Callback* callback) {
	syncCallback = callback;
}

byte PrefetchSimpleLampMatrix::internalGetColumn(LampPattern* pattern, int columnNumber) {
	return pattern->getLampBank(columnNumber);
}

void PrefetchSimpleLampMatrix::internalSetPattern(LampPattern* newPattern) {
	if (attachedPattern != newPattern) {
		if (attachedPattern != NULL) {
			attachedPattern->detached();
		}
		attachedPattern = newPattern;
		if (attachedPattern != NULL) {
			attachedPattern->attached();
			prefetchedColumnValue = attachedPattern->getLampBank(currentColumn);
		}
	}
}

void PrefetchSimpleLampMatrix::internalEndOfMatrixSync(LampPattern* pattern) {
	pattern->endOfMatrixSync();
}

} /* namespace us_cownet_lamps */

