/*
 * Ticker.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#include "Ticker.h"

#include "TimerUtil.h"

#include <Arduino.h>

namespace us_cownet_timers {

Ticker::Ticker(unsigned long periodMicrosIn)
: periodMicros(periodMicrosIn), lastTick(0)
{
}

Ticker::~Ticker() {
}

void Ticker::setPeriod(unsigned long periodInMicrosIn) {
	periodMicros = (periodInMicrosIn);
}

bool Ticker::isTime() {
	unsigned long now = TimerUtil::INSTANCE.currentTimeMicros();
	if (now - lastTick > periodMicros) {
		lastTick = now;
		return true;
	} else {
		return false;
	}
}

} /* namespace us_cownet_testing */
