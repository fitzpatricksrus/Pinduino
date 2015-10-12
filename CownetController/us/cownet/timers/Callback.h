/*
 * Callback.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TIMERS_CALLBACK_H_
#define US_COWNET_TIMERS_CALLBACK_H_

namespace us_cownet_timers {

class Callback {
public:
	Callback();
	virtual ~Callback();

	virtual void call() = 0;
};

} /* namespace us_cownet_timers */

#endif /* US_COWNET_TIMERS_CALLBACK_H_ */
