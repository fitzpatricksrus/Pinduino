/*
 * Timer.h
 *
 *  Created on: Jul 28, 2015
 *      Author: jfitzpatrick
 */

#ifndef TIMER_H_
#define TIMER_H_

namespace us_cownet_timers {

class Timer {
public:
	Timer(unsigned long periodInMicrosIn);
	virtual ~Timer();
	void setPeriod(unsigned long periodInMicrosIn);
	unsigned long getPeriod();
	bool isTime();

private:
	unsigned long periodMicros;
	unsigned long lastMicro;
};

} /* namespace us_cownet_timers */

#endif /* TIMER_H_ */
