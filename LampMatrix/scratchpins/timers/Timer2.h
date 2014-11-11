/*
 * Timer2.h
 *
 *  Created on: Nov 9, 2014
 *      Author: Dad
 */

#ifndef SCRATCHPINS_TIMERS_TIMER2_H_
#define SCRATCHPINS_TIMERS_TIMER2_H_

#include "Timer.h"

namespace timers {

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.
class Timer2 : public Timer {
public:
	enum Prescalar {
		TIMER_OFF = 0b00000000,
		//prescalar
		PS1 = 0b00000001, 		// 0.0000625 ms
		PS8 = 0b00000010, 		// 0.0005 ms
		PS32 = 0b00000011, 		// 0.004 ms
		PS64 = 0b00000100, 		// 0.016 ms
		PS128 = 0b0000101,		// 0.064 ms
		PS256 = 0b00000110,
		PS1024 = 0b00000111,
	};

	Timer2();
	virtual ~Timer2();
	virtual void init();
	virtual void setPrescalar(Prescalar p);

	// Pins 11 and 3: controlled by timer1
	// Pins 9 and10:: controlled by timer1 on Mega

	void loopA(); // used by ISR
	void loopB(); // used by ISR

	static Timer2& INSTANCE;

protected:
	virtual void togglePin(bool callbackA, bool toggleOn);
	virtual void setCallbackTicks(bool callbackA, unsigned int ticks);
	virtual void enableCallback(bool callbackA);
	virtual void disableCallback(bool callbackA);

	static const byte prescalarValueMask;
	static const byte prescalarValues[];
};

} // namespace timers

#endif /* SCRATCHPINS_TIMERS_TIMER2_H_ */
