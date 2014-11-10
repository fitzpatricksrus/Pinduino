/*
 * Timer1.h
 *
 *  Created on: Nov 9, 2014
 *      Author: Dad
 */

#ifndef SCRATCHPINS_TIMERS_TIMER1_H_
#define SCRATCHPINS_TIMERS_TIMER1_H_

#include <Arduino.h>
#include "Timer.h"

namespace timers {

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.
class Timer1 : public Timer {
public:
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

	Timer1();
	virtual ~Timer1();
	virtual void init();
	virtual void setTicks(unsigned int ticks);
	virtual void setPrescalar(Prescalar p);

	// Pins 9 and 10: controlled by timer1
	// Pins 11 and 12: controlled by timer1 on Mega
	virtual void togglePinA(bool toggleOn);
	virtual void togglePinB(bool toggleOn);

	void loopA(); // used by ISR
	void loopB(); // used by ISR

protected:
	virtual void setCallbackTicks(bool callbackA, unsigned int ticks);
	virtual void enableCallback(bool callbackA);
	virtual void disableCallback(bool callbackA);


	static const byte prescalarValueMask;
	static const byte prescalarValues[];

	static Timer1& INSTANCE;
};

} // namespace timers

#endif /* SCRATCHPINS_TIMERS_TIMER1_H_ */
