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
		PS32,		// timer 2 only
		PS64, 		// 0.004 ms
		PS128,		// timer 2 only
		PS256, 		// 0.016 ms
		PS1024,		// 0.064 ms
		PSExternalFalling,
		PSExternalRising };

	void init();
	void addCallback(Callback* function, Prescalar p, unsigned int ticks);
	void enableCallbacks();
	void disableCallbacks();
	void setPrescalar(Prescalar p);
	void setTicks(unsigned int ticks);

	static Timer& TIMER1;

	static Timer& T2;

protected:
	static const byte MAX_CALLBACKS = 8;
	Timer();
	Timer::Callback* callbacks[MAX_CALLBACKS];

	virtual void initInternal() = 0;
	virtual void enableCallbacksInternal() = 0;
	virtual void disableCallbacksInternal() = 0;
	virtual void setPrescalarInternal(Prescalar p) = 0;
	virtual void setTicksInternal(unsigned int ticks) = 0;
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
