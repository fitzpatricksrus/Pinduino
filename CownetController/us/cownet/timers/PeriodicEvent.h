/*
 * PeriodicEvent.h
 *
 *  Created on: Oct 14, 2015
 *      Author: jfitzpatrick
 */

#ifndef PERIODICEVENT_H_
#define PERIODICEVENT_H_

namespace us_cownet_timers {

//-std=c++0x

class PeriodicEvent {
public:
	PeriodicEvent();
	PeriodicEvent(const PeriodicEvent& other);
	PeriodicEvent(const PeriodicEvent&& other);
	~PeriodicEvent();
	PeriodicEvent& operator=(const PeriodicEvent& other);

	bool isTime();

	void setTicks(long ticks);
	void setTime(long time);

	static PeriodicEvent forTicks(long ticks);
	static PeriodicEvent forTime(long time);
	static const PeriodicEvent& NEVER;

private:
	long lastTock;
	long period;
	bool isTicks;
};

} /* namespace us_cownet_timers */

#endif /* PERIODICEVENT_H_ */
