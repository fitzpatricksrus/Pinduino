/*
 * Timer.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#include "Timer.h"

#include <Arduino.h>

#ifdef __DEBUG__
#define println(x) if (Serial) Serial.println(x);
#define print(x) if (Serial) Serial.print(x);
#else
#define println(x)
#define print(x)
#endif

namespace scheduler {

void Timer::Callback::setup() {
}

void Timer::Callback::loop() {
}

Timer::Timer()
	: callbacks()
{
	for (int8_t i = MAX_CALLBACKS - 1; i >= 0; i--) {
		callbacks[i] = 0;
	}
}

Timer::~Timer() {
}

void Timer::addCallback(Callback* callbackIn, Prescalar p, unsigned int ticks) {
	disableCallbacks();
	for (int8_t i = MAX_CALLBACKS - 1; i >= 0; i--) {
		if (callbacks[i] == callbackIn) {
			return;
		}
	}
	for (int8_t i = MAX_CALLBACKS - 1; i >= 0; i--) {
		if (callbacks[i] == 0) {
			callbacks[i] = callbackIn;
			callbackIn->setup();
			break;
		}
	}
	setPrescalar(p);
	setTicks(ticks);
	// enable timer compare interrupt:
	enableCallbacks();
}

void Timer::init() {
	initInternal();
}
void Timer::enableCallbacks() {
	enableCallbacksInternal();
}
void Timer::disableCallbacks() {
	disableCallbacksInternal();
}
void Timer::setPrescalar(Prescalar p) {
	setPrescalarInternal(p);
}
void Timer::setTicks(unsigned int ticks) {
	setTicksInternal(ticks);
}

static int timerTicks = 0;

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.
class Timer1 : public Timer {
public:
	Timer1();
	virtual ~Timer1();
	virtual void initInternal();
	virtual void enableCallbacksInternal();
	virtual void disableCallbacksInternal();
	virtual void setPrescalarInternal(Prescalar p);
	virtual void setTicksInternal(unsigned int ticks);

	void loop(); // used by ISR

	static const byte prescalarValueMask;
	static const byte prescalarValues[];

};

const byte Timer1::prescalarValueMask = ~((1<<CS10) | (1<<CS11) | (1<<CS12));
const byte Timer1::prescalarValues[] = {
		0,
		(1<<CS10),
		(1<<CS11),
		0,
		(1<<CS10) | (1<<CS11),
		0,
		(1<<CS12),
		(1<<CS12) | (1<<CS10),
		(1<<CS12) | (1<<CS11),
		(1<<CS12) | (1<<CS11) | (1<<CS10)
};

Timer1::Timer1() {
}

Timer1::~Timer1() {
}

void Timer1::initInternal() {
    disableCallbacks();
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    setTicks(32000);
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    setPrescalar(TIMER_OFF);
    // enable global interrupts:
}

void Timer1::enableCallbacksInternal() {
	TIMSK1 = TIMSK1 | (1 << OCIE1A);
}

void Timer1::disableCallbacksInternal() {
    TIMSK1 = TIMSK1 & ~(1 << OCIE1A);
}

void Timer1::setPrescalarInternal(Prescalar p) {
	TCCR1B = (TCCR1B & prescalarValueMask) | prescalarValues[p];
}
void Timer1::setTicksInternal(unsigned int desiredTicks) {
	OCR1A = desiredTicks;
	uint16_t ticksPassedThisCycle = TCNT1;
	// try to get close to the range we, keeping accumulated ticks if there are any.
	if (ticksPassedThisCycle > desiredTicks) {
		uint16_t overflow = (ticksPassedThisCycle - desiredTicks) % desiredTicks;  // handle 1 overflow, but no more
		TCNT1H = overflow >> 8;
		TCNT1L = overflow & 0xFF;
	} else {
		uint16_t remaining = desiredTicks - ticksPassedThisCycle;
		TCNT1H = remaining >> 8;
		TCNT1L = remaining & 0xFF;
	}
}

void Timer1::loop() {
	for (int8_t i = MAX_CALLBACKS - 1; i >= 0; i--) {
		if (callbacks[i]) {
			callbacks[i]->loop();
		}
	}
}

static Timer1 timer1Instance;
Timer& Timer::TIMER1 = timer1Instance;

ISR(TIMER1_COMPA_vect)
{
	timer1Instance.loop();
}

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.
class Timer2 : public Timer {
public:
	Timer2();
	virtual ~Timer2();
	virtual void initInternal();
	virtual void enableCallbacksInternal();
	virtual void disableCallbacksInternal();
	virtual void setPrescalarInternal(Prescalar p);
	virtual void setTicksInternal(unsigned int ticks);

	void loop(); // used by ISR

	static byte prescalarValueMask;
	static byte prescalarValues[];

};

byte Timer2::prescalarValueMask = ~((1<<CS20) | (1<<CS21) | (1<<CS22));
byte Timer2::prescalarValues[] = {
		0,
		(1<<CS20),
		(1<<CS21),
		0,
		(1<<CS20) | (1<<CS21),
		0,
		(1<<CS22),
		(1<<CS22) | (1<<CS20),
		(1<<CS22) | (1<<CS21),
		(1<<CS22) | (1<<CS21) | (1<<CS20)
};

Timer2::Timer2() {
}

Timer2::~Timer2() {
}

void Timer2::initInternal() {
    disableCallbacks();
    TCCR2A = 0;     // set entire TCCR1A register to 0
    TCCR2B = 0;     // same for TCCR1B

    setTicks(32000);
    // turn on CTC mode:
    TCCR2B |= (1 << WGM22);
    setPrescalar(TIMER_OFF);
    // enable global interrupts:
}

void Timer2::enableCallbacksInternal() {
	TIMSK2 = TIMSK2 | (1 << OCIE2A);
}

void Timer2::disableCallbacksInternal() {
    TIMSK2 = TIMSK2 & ~(1 << OCIE2A);
}


void Timer2::setPrescalarInternal(Prescalar p) {
	TCCR2B = (TCCR2B & prescalarValueMask) | prescalarValues[p];
}
void Timer2::setTicksInternal(unsigned int desiredTicks) {
	OCR2A = desiredTicks;
	unsigned long ticksPassedThisCycle = TCNT2;
	// try to get close to the range we, keeping accumulated ticks if there are any.
	if (ticksPassedThisCycle > desiredTicks) {
		TCNT2 = 0;
	} else {
		byte remaining = desiredTicks - ticksPassedThisCycle;
		TCNT2 = remaining;
	}
}

void Timer2::loop() {
	for (int8_t i = MAX_CALLBACKS - 1; i >= 0; i--) {
		if (callbacks[i]) {
			callbacks[i]->loop();
		}
	}
}

static Timer2 Timer2Instance;
Timer& Timer::T2 = Timer2Instance;

ISR(TIMER2_COMPA_vect)
{
	Timer2Instance.loop();
}


} /* namespace Tests */
