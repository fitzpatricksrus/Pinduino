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
		TIMER_OFF = B00000000,
		//prescalar
		PS1 = B00000001, 		// 0.0000625 ms
		PS8 = B00000010, 		// 0.0005 ms
		PS64 = B00000011, 		// 0.004 ms
		PS256 = B00000100, 		// 0.016 ms
		PS1024 = B0000101,		// 0.064 ms
		PSExternalFalling = B00000110,
		PSExternalRising = B00000111,

		// duration of a tick
		us0p0625 = 1, 	// 0.0625 us
		us0p5 = 2, 		// 0.5 us
		us2 = 3,		// 2 us timer 2 only
		us4 = 4, 		// 4 us
		us8 = 5,		// 8 us timer 2 only
		us16 = 6, 		// 16 us
		us64 = 7,		// 64 us

		// ticks per second
		t16000000 = 1, 	// 0.0625 us
		t2000000 = 2, 	// 0.5 us
		t500000 = 3,	// 2 us timer 2 only
		t250000 = 4, 	// 4 us
		t125000 = 5,	// 8 us timer 2 only
		t62500 = 6, 	// 16 us
		t15625 = 7,		// 64 us

	};

	void init();
	void addCallback(Callback* function, Prescalar p, unsigned int ticks);
	void enableCallbacks();
	void disableCallbacks();
	void setPrescalar(Prescalar p);
	void setTicks(unsigned int ticks);

	static Timer& timer1;
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

} /* namespace scheduler */

#endif /* TIMER_H_ */
