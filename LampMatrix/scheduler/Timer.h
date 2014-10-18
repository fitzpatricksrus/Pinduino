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
		virtual void setup() = 0;
		virtual void run() = 0;
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

	Timer::Callback* getCallback() const;
	virtual void setCallback(Timer::Callback* callback, Prescalar p, int ticks);
	virtual void enableCallbacks() = 0;
	virtual void disableCallBacks() = 0;
	virtual void setPrescalar(Prescalar p) = 0;
	virtual void setTicks(int ticks) = 0;

	static Timer& TIMER1;

protected:
	Timer();

private:
	Timer::Callback* callback;
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
