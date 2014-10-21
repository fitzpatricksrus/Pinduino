/*
 * Timer.h
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>

namespace scheduler {

class Timer {
public:
	class Callback {
	public:
		virtual void setup();
		virtual void loop();
	};

	virtual ~Timer();

	enum Prescalar {
		TIMER_OFF,
		PS1, 		// 0.0000625 ms
		PS8, 		// 0.0005 ms
		PS64, 		// 0.004 ms
		PS256, 		// 0.016 ms
		PS1024,		// 0.064 ms
		PSExternalFalling, PSExternalRising };

	virtual void init() = 0;
	virtual void addCallback(Callback* function, Prescalar p, unsigned int ticks);
	virtual void enableCallbacks() = 0;
	virtual void disableCallbacks() = 0;
	virtual void setPrescalar(Prescalar p) = 0;
	virtual void setTicks(unsigned int ticks) = 0;

	static Timer& TIMER1;

protected:
	Timer();
	Timer::Callback* callbacks[8];
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
