/*
 * PeriodicEvent.h
 *
 *  Created on: Jul 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TIMERS_PERIODICEVENT_H_
#define US_COWNET_TIMERS_PERIODICEVENT_H_

namespace us_cownet_timers {

class PeriodicEvent {
public:
	PeriodicEvent(bool isTickerIn, unsigned long periodIn);
	PeriodicEvent(const PeriodicEvent& other);
	virtual ~PeriodicEvent();

	void setPeriod(unsigned long periodIn) { period = periodIn; }
	unsigned long getPeriod() { return period; }
	bool isTime();

	bool isTicker() { return isTickerEvent; }
	void setIsTicker(bool isTickerIn) { isTickerEvent = isTickerIn; }

private:
	bool isTickerEvent;
	unsigned long period;
	unsigned long lastEvent;

};

} /* namespace us_cownet_timers */

#endif /* US_COWNET_TIMERS_PERIODICEVENT_H_ */
