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

Timer::Callback EmptyCallback;

// a single instance of this class is reused
// for implementing the function callback.
class FunctionCallback : public Timer::Callback {
public:
	virtual ~FunctionCallback() {}
	virtual void loop();

	Timer::CallbackFunction f;
};

void FunctionCallback::loop() {
	(*f)();
}

static FunctionCallback functionCallback;

Timer::Timer()
	: callback(&EmptyCallback)
{
}

Timer::~Timer() {
}

void Timer::setCallback(CallbackFunction callback, Prescalar p, unsigned int ticks) {
	if (callback) {
		functionCallback.f = callback;
		setCallback(&functionCallback, p, ticks);
	} else {
		setCallback(&EmptyCallback, p, ticks);
	}
}

void Timer::setCallback(Timer::Callback* callbackIn, Prescalar p, unsigned int ticks) {
	disableCallbacks();
	if (!callbackIn) callbackIn = &EmptyCallback;
	callbackIn->setup();
//	cli();
	callback = callbackIn;
	setPrescalar(p);
	setTicks(ticks);
	// enable timer compare interrupt:
	enableCallbacks();
//	sei();
}

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.
class Timer1: public Timer {
public:
	Timer1();
	virtual ~Timer1();
	virtual void init();
	virtual void resetTimer();
	virtual void enableCallbacks();
	virtual void disableCallbacks();
	virtual void setPrescalar(Prescalar p);
	virtual void setTicks(unsigned int ticks);

	void loop(); // used by ISR
};

Timer1::Timer1() {
}

Timer1::~Timer1() {
}

void Timer1::init() {
	println("Timer1::init");
//    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    setTicks(32000);
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    setPrescalar(TIMER_OFF);
    disableCallbacks();
    // enable global interrupts:
//    sei();
}

void Timer1::resetTimer() {
	TCNT1H = 0;
	TCNT1L = 0;
}

void Timer1::enableCallbacks() {
	print("TIMSK1: enable ");
	println(((int)(TIMSK1 | (1 << OCIE1A))));
	TIMSK1 = TIMSK1 | (1 << OCIE1A);
}

void Timer1::disableCallbacks() {
	print("TIMSK1: disable ");
	println(((int)(TIMSK1 & ~(1 << OCIE1A))));
    TIMSK1 = TIMSK1 & ~(1 << OCIE1A);
}

static byte prescalarValueMask = ~((1<<CS10) | (1<<CS11) | (1<<CS12));
static byte prescalarValues[] = {
		0,
		(1<<CS10),
		(1<<CS11),
		(1<<CS10) | (1<<CS11),
		(1<<CS12),
		(1<<CS12) | (1<<CS10),
		(1<<CS12) | (1<<CS11),
		(1<<CS12) | (1<<CS11) | (1<<CS10)
};

void Timer1::setPrescalar(Prescalar p) {
	print("setPrescalar: "); print(p); print("  TCCR1B: ");
	println(((int)((TCCR1B & prescalarValueMask) | prescalarValues[p])));
	TCCR1B = (TCCR1B & prescalarValueMask) | prescalarValues[p];
}
void Timer1::setTicks(unsigned int ticks) {
//	print("setTicks: "); println(ticks);
	OCR1A = ticks;
}

void Timer1::loop() {
	callback->loop();
}

static Timer1 timer1Instance;
Timer& Timer::TIMER1 = timer1Instance;

ISR(TIMER1_COMPA_vect)
{
	timer1Instance.loop();
}


} /* namespace Tests */
