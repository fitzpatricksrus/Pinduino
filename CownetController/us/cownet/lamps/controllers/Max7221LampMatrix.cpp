/*
 * Max7221LampMatrix.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: jfitzpatrick
 */

#include "Max7221LampMatrix.h"

namespace us_cownet_lamps_tests {

Max7221LampMatrix::Max7221LampMatrix()
: refreshFrequency(0), pattern(NULL)
{
}

Max7221LampMatrix::Max7221LampMatrix(long refreshFrequencyIn)
: refreshFrequency(refreshFrequencyIn), pattern(NULL)
{
}

Max7221LampMatrix::~Max7221LampMatrix() {
}

LampPattern* Max7221LampMatrix::getPattern() {
	return pattern;
}

void Max7221LampMatrix::setPattern(LampPattern* newPattern) {
	if (pattern == newPattern) return;
	if (pattern != NULL) {
		pattern->detached();
	}
	pattern = newPattern;
	if (pattern != NULL) {
		pattern->attached();
	}

	TimerUtil::INSTANCE.attachTickerCallback(&thisCallback, ticks);
	if (pattern == NULL && newPattern != NULL) {
		// kick start the first refresh.
		if (pattern != newPattern) {
			if (pattern != NULL) {
				pattern->detached();
			}
			pattern = newPattern;
			if (pattern != NULL) {
				pattern->attached();
				prefetchedColumnValue = pattern->getColumn(currentColumn);
			}
		}
	}
}

} /* namespace us_cownet_lamps_tests */
