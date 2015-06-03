/*
 * TimerUtil.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#include "TimerUtil.h"

#include <TimerThree.h>

namespace us_cownet_lamps_simple {

TimerUtil::TimerUtil() {

}

TimerUtil::~TimerUtil() {
}

void TimerUtil::attachInterrupt(void (*isr)(), long microseconds) {
	Timer3.attachInterrupt(isr, microseconds);
}

void TimerUtil::detachInterrupt() {
	Timer3.detachInterrupt();
}

} /* namespace pins */
