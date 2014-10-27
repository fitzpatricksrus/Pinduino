/*
 * Timer.h
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>
#include "Tests/Debug.h"

class Timer {
public:
	class Callback {
	public:
		virtual void setup();
		virtual void loop();
	};

	virtual ~Timer();

	enum Prescalar {
		TIMER_OFF = B00000000,
		PS1 = B00000001, 		// 0.0000625 ms
		PS8 = B00000010, 		// 0.0005 ms
		PS64 = B00000011, 		// 0.004 ms
		PS256 = B00000100, 		// 0.016 ms
		PS1024 = B0000101,		// 0.064 ms
		PSExternalFalling = B00000110,
		PSExternalRising = B00000111 };

	void init();
	void addCallback(Callback* function, Prescalar p, unsigned int ticks);
	void enableCallbacks();
	void disableCallbacks();
	void setPrescalar(Prescalar p);
	void setTicks(unsigned int ticks);

	static Timer& timer1;
	static Timer& timer2;
	static Timer& debugTimer;
	static void tickDebugTimer(unsigned long currentTime);

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

class TimerCallback : public Timer::Callback {
public:
	TimerCallback();
	virtual void loop();

	Tests::DebugCounter timerCnt;
};


#endif /* TIMER_H_ */
