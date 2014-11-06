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

	void init();
	void addCallback(Callback* function);
	void removeCallback(Callback* function);
	void enableCallbacks();
	void disableCallbacks();
	void setTicks(unsigned int ticks);

	static Timer& timer1;
	static Timer& timer2;
	static Timer& debugTimer;
	static void tickDebugTimer(unsigned long currentTime);

protected:
	static const byte MAX_CALLBACKS = 8;
	Timer();
	byte callbackCount;
	Timer::Callback* callbacks[MAX_CALLBACKS];

	virtual void initInternal() = 0;
	virtual void enableCallbacksInternal() = 0;
	virtual void disableCallbacksInternal() = 0;
	virtual void setTicksInternal(unsigned int ticks) = 0;
};


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

	virtual void setPrescalar(Prescalar p);


	Timer1();
	virtual ~Timer1();
	virtual void initInternal();
	virtual void enableCallbacksInternal();
	virtual void disableCallbacksInternal();
	virtual void setTicksInternal(unsigned int ticks);

	void loop(); // used by ISR

	static const byte prescalarValueMask;
	static const byte prescalarValues[];

	static Timer1& INSTANCE;
};

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.
class Timer2 : public Timer {
public:
	enum Prescalar {
		TIMER_OFF = B00000000,
		//prescalar
		PS1 = B00000001, 		// 0.0000625 ms
		PS8 = B00000010, 		// 0.0005 ms
		PS32 = B00000011, 		// 0.004 ms
		PS64 = B00000100, 		// 0.016 ms
		PS128 = B0000101,		// 0.064 ms
		PS256 = B00000110,
		PS1024 = B00000111,
	};

	virtual void setPrescalar(Prescalar p);


	Timer2();
	virtual ~Timer2();
	virtual void initInternal();
	virtual void enableCallbacksInternal();
	virtual void disableCallbacksInternal();
	virtual void setTicksInternal(unsigned int ticks);

	void loop(); // used by ISR

	static const byte prescalarValueMask;
	static const byte prescalarValues[];

	static Timer2& INSTANCE;
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
