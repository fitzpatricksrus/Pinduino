/*
 * Timer.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#include "Timer.h"

#include <Arduino.h>
#include "../scratchpins/timers/TimerVectors.h"
#define _ENABLE_X


namespace scheduler {

void Timer::Callback::setup() {
}

void Timer::Callback::loop() {
}

Timer::Timer()
	: callbackCount(0), callbacks()
{
	for (byte i = 0; i < MAX_CALLBACKS; i++) {
		callbacks[i] = 0;
	}
}

Timer::~Timer() {
}

void Timer::addCallback(Callback* callbackIn) {
	disableCallbacks();
	for (byte i = 0; i < callbackCount; i++) {
		if (callbacks[i] == callbackIn) {
			// callback is already here.  just leave.
			enableCallbacks();
			return;
		}
	}
	callbacks[callbackCount++] = callbackIn;
	callbackIn->setup();
	// enable timer compare interrupt:
	enableCallbacks();
}

void Timer::removeCallback(Callback* callbackIn) {
	disableCallbacks();
	for (byte i = 0; i < callbackCount; i++) {
		if (callbacks[i] == callbackIn) {
			callbackCount--;
			callbacks[i] = callbacks[callbackCount];
			callbacks[callbackCount] = 0;
		}
	}
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
void Timer::setTicks(unsigned int ticks) {
	setTicksInternal(ticks);
}

//-----------------------------------------------------------------------
// DebugTimer is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.
class DebugTimer : public Timer {
public:
	DebugTimer();
	virtual ~DebugTimer();
	virtual void initInternal();
	virtual void enableCallbacksInternal();
	virtual void disableCallbacksInternal();
	virtual void setTicksInternal(unsigned int ticks);

	unsigned long ticksPerCallback;
	unsigned long lastCallbackTime;
	bool callbacksEnabled;
};

DebugTimer::DebugTimer()
: ticksPerCallback(0), lastCallbackTime(0), callbacksEnabled(false)
{
}

DebugTimer::~DebugTimer() {
}

void DebugTimer::initInternal() {
}

void DebugTimer::enableCallbacksInternal() {
	callbacksEnabled = true;
}

void DebugTimer::disableCallbacksInternal() {
	callbacksEnabled = false;
}

void DebugTimer::setTicksInternal(unsigned int desiredTicks) {
	ticksPerCallback = desiredTicks;
}

static DebugTimer debugTimerInstance;
Timer& Timer::debugTimer = debugTimerInstance;

void Timer::tickDebugTimer(unsigned long currentTime) {
	if (currentTime - debugTimerInstance.lastCallbackTime >= debugTimerInstance.ticksPerCallback) {
		if (debugTimerInstance.callbacksEnabled) {
			for (int8_t i = MAX_CALLBACKS - 1; i >= 0; i--) {
				if (debugTimerInstance.callbacks[i]) {
					debugTimerInstance.callbacks[i]->loop();
				}
			}
		}
		debugTimerInstance.lastCallbackTime = currentTime;
	}
}

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.

const byte Timer1::prescalarValueMask = ~((1<<CS10) | (1<<CS11) | (1<<CS12));
const byte Timer1::prescalarValues[] = {
		0,
		(1<<CS10),
		(1<<CS11),
		(1<<CS10) | (1<<CS11),
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
    // initialize Timer1*/
    cli();          // disable global interrupts
    disableCallbacksInternal();

    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR1A = 32000;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable global interrupts:
    sei();

}

static void Timer1ACallback();
void Timer1::enableCallbacksInternal() {
	timers::TimerVectors::timer1aVector.attachInterrupt(&Timer1ACallback);
	TIMSK1 = TIMSK1 | (1 << OCIE1A);
}

void Timer1::disableCallbacksInternal() {
	timers::TimerVectors::timer1aVector.detachInterrupt();
    TIMSK1 = TIMSK1 & ~(1 << OCIE1A);
}

void Timer1::setPrescalar(Prescalar p) {
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
	}
}

void Timer1::loop() {
	for (int8_t i = callbackCount - 1; i >= 0; i--) {
		callbacks[i]->loop();
	}
}

static Timer1 timer1Instance;
Timer& Timer::timer1 = timer1Instance;
Timer1& Timer1::INSTANCE = timer1Instance;

static void Timer1ACallback() {
	timer1Instance.loop();
}
#ifdef _ENABLE_
ISR(TIMER1_COMPA_vect)
{
	timer1Instance.loop();
}
#endif

//-----------------------------------------------------------------------
// Timer2 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.

const byte Timer2::prescalarValueMask = ~((1<<CS20) | (1<<CS21) | (1<<CS22));
const byte Timer2::prescalarValues[] = {
		0,
		(1<<CS20),
		(1<<CS21),
		(1<<CS20) | (1<<CS21),
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
    // initialize Timer2*/
    cli();          // disable global interrupts
    disableCallbacksInternal();

    TCCR2A = 0;     // set entire TCCR1A register to 0
    TCCR2B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR2A = 255;
    // turn on CTC mode:
    TCCR2B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS22);
    // enable global interrupts:
    sei();

}

static void Timer2ACallback();
void Timer2::enableCallbacksInternal() {
	timers::TimerVectors::timer2aVector.attachInterrupt(&Timer2ACallback);
	TIMSK2 = TIMSK2 | (1 << OCIE2A);
}

void Timer2::disableCallbacksInternal() {
	timers::TimerVectors::timer2aVector.detachInterrupt();
    TIMSK2 = TIMSK2 & ~(1 << OCIE2A);
}

void Timer2::setPrescalar(Prescalar p) {
	TCCR2B = (TCCR2B & prescalarValueMask) | prescalarValues[p];
}
void Timer2::setTicksInternal(unsigned int desiredTicks) {
	OCR2A = desiredTicks;
	uint8_t ticksPassedThisCycle = TCNT2;
	// try to get close to the range we, keeping accumulated ticks if there are any.

	if (ticksPassedThisCycle > desiredTicks) {
		uint16_t overflow = (ticksPassedThisCycle - desiredTicks) % desiredTicks;  // handle 1 overflow, but no more
		TCNT2 = overflow & 0xFF;
	}
}

void Timer2::loop() {
	for (int8_t i = callbackCount - 1; i >= 0; i--) {
		callbacks[i]->loop();
	}
}

static Timer2 Timer2Instance;
Timer& Timer::timer2 = Timer2Instance;
Timer2& Timer2::INSTANCE = Timer2Instance;

static void Timer2ACallback() {
	Timer2Instance.loop();
}

#ifdef _ENABLE_
ISR(TIMER2_COMPA_vect)
{
	Timer2Instance.loop();
}
#endif

} /* namespace Tests */
