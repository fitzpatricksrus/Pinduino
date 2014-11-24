/*
 * TimerVectors.cpp
 *
 *  Created on: Nov 23, 2014
 *      Author: Dad
 */

#include "TimerVectors.h"
#include <arduino.h>

namespace timers {

TimerVectors::TimerVectors()
: callback(0)
{
}

TimerVectors& TimerVectors::attachInterrupt(ISR callbackIn) {
	callback = callbackIn;
	return *this;
}

TimerVectors& TimerVectors::detachInterrupt() {
	callback = 0;
	return *this;
}

void TimerVectors::doCallback() {
	if (callback != 0) {
		(*callback)();
	}
}

static TimerVectors a1;
static TimerVectors b1;
static TimerVectors a2;
static TimerVectors b2;
TimerVectors& TimerVectors::timer1aVector = a1;
TimerVectors& TimerVectors::timer1bVector = b1;
TimerVectors& TimerVectors::timer2aVector = a2;
TimerVectors& TimerVectors::timer2bVector = b2;

ISR(TIMER1_COMPA_vect)
{
	a1.doCallback();
}

ISR(TIMER1_COMPB_vect)
{
	b1.doCallback();
}

ISR(TIMER2_COMPA_vect)
{
	a2.doCallback();
}

ISR(TIMER2_COMPB_vect)
{
	b2.doCallback();
}


} /* namespace timers */
