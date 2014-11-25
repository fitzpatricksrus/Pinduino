/*
 * Timer2.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: Dad
 */

#include "Timer2.h"
#include <Arduino.h>

namespace timers {

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

void Timer2::init() {
    // initialize Timer1*/
    cli();          // disable global interrupts

    TCCR2A = 0;     // set entire TCCR1A register to 0
    TCCR2B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR2A = 255;
    OCR2B = 255;
    // turn on CTC mode:
    TCCR2B |= (1 << WGM22);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS22);
    // enable global interrupts:
    sei();

}

void Timer2::enableCallback(bool callbackA) {
	if (callbackA) {
		TIMSK2 = TIMSK2 | (1 << OCIE2A);
	} else {
		TIMSK2 = TIMSK2 | (1 << OCIE2B);
	}
}

void Timer2::disableCallback(bool callbackA) {
	if (callbackA) {
		TIMSK2 = TIMSK2 & ~(1 << OCIE2A);
	} else {
		TIMSK2 = TIMSK2 & ~(1 << OCIE2B);
	}
}

void Timer2::setPrescalar(Prescalar p) {
	TCCR2B = (TCCR2B & prescalarValueMask) | prescalarValues[p];
}

void Timer2::setCallbackTicks(bool callbackA, unsigned int desiredTicks) {
	if (callbackA) {
		OCR1A = desiredTicks;
	} else {
		OCR1B = desiredTicks;
	}
}

void Timer2::togglePin(bool callbackA, bool toggleOn) {
	//hey jf - implement this
}

void Timer2::loopA() {
	if (callbackA) callbackA->loop();
}

void Timer2::loopB() {
	if (callbackB) callbackB->loop();
}

static Timer2 timer1Instance;
Timer2& Timer2::INSTANCE = timer1Instance;

#ifdef _ENABLE_
ISR(TIMER2_COMPA_vect)
{
	timer1Instance.loopA();
}

ISR(TIMER2_COMPB_vect)
{
	timer1Instance.loopB();
}
#endif

} //namespace timers
