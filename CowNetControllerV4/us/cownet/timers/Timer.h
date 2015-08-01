/*
 * Timer.h
 *
 *  Created on: Jul 28, 2015
 *      Author: jfitzpatrick
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "PeriodicEvent.h"

namespace us_cownet_timers {

class Timer : public PeriodicEvent {
public:
	Timer(unsigned long periodInMicrosIn) : PeriodicEvent(false, periodInMicrosIn) {}
	virtual ~Timer() {}
};

} /* namespace us_cownet_timers */

#endif /* TIMER_H_ */
