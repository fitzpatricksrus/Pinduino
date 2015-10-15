/*
 * PeriodicEvent.h
 *
 *  Created on: Oct 14, 2015
 *      Author: jfitzpatrick
 */

#ifndef PERIODICEVENT_H_
#define PERIODICEVENT_H_

namespace us_cownet_timers {

class PeriodicEvent {
public:
	PeriodicEvent();
	virtual ~PeriodicEvent();

	virtual bool isTime() = 0;
};

} /* namespace us_cownet_timers */

#endif /* PERIODICEVENT_H_ */
