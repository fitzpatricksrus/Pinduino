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
  thisCallback(this, &PrefetchSimpleLampMatrix::tock), prefetchedColumnValue(0)
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
	controller->writeCol((byte)0);
	controller->writeRow(prefetchedColumnValue);
	controller->writeCol((byte)(1 << currentColumn));
	currentColumn = (currentColumn + 1) % attachedPattern->getColCount();
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
	return pattern->getColumn(columnNumber);
}

void PrefetchSimpleLampMatrix::internalSetPattern(LampPattern* newPattern) {
	if (attachedPattern != newPattern) {
		if (attachedPattern != NULL) {
			attachedPattern->detached();
		}
		attachedPattern = newPattern;
		if (attachedPattern != NULL) {
			attachedPattern->attached();
			prefetchedColumnValue = attachedPattern->getColumn(currentColumn);
		}
	}
}

void internalEndOfMatrixSync(LampPattern* pattern) {
	pattern->endOfMatrixSync();
}

} /* namespace us_cownet_lamps */

