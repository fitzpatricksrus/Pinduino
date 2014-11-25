/*
 * TimerVectors.h
 *
 *  Created on: Nov 23, 2014
 *      Author: Dad
 */

#ifndef TIMERS_TIMERVECTORS_H_
#define TIMERS_TIMERVECTORS_H_

namespace timers {

class TimerVectors {
public:
	typedef void (*ISR)();

	TimerVectors();

	TimerVectors& attachInterrupt(ISR callback);
	TimerVectors& detachInterrupt(void);

	void doCallback();

	static TimerVectors& timer1aVector;
	static TimerVectors& timer1bVector;
	static TimerVectors& timer2aVector;
	static TimerVectors& timer2bVector;

private:
	ISR callback;
};

} /* namespace timers */

#endif /* TIMERS_TIMERVECTORS_H_ */
