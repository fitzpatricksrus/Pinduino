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

Ticker::Ticker(unsigned long periodTicksIn)
: periodTicks(periodTicksIn), lastTick(0)
{
}

Ticker::~Ticker() {
}

void Ticker::setPeriod(unsigned long periodTicksIn) {
	periodTicks = (periodTicksIn);
}

unsigned long Ticker::getPeriod() {
	return periodTicks;
}

bool Ticker::isTime() {
	unsigned long now = TimerUtil::INSTANCE.currentTicks();
	if (now - lastTick > periodTicks) {
		lastTick = now;
		return true;
	} else {
		return false;
	}
}

} /* namespace us_cownet_testing */
