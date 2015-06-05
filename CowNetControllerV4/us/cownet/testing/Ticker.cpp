/*
 * Ticker.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#include "Ticker.h"

#include <Arduino.h>

namespace us_cownet_testing {

Ticker::Ticker(unsigned long periodMicrosIn)
: periodMicros(periodMicrosIn), lastTick(0)
{
}

Ticker::~Ticker() {
}

bool Ticker::isTime() {
	unsigned long now = micros();
	if (now - lastTick > periodMicros) {
		lastTick = now;
		return true;
	} else {
		return false;
	}
}

} /* namespace us_cownet_testing */
