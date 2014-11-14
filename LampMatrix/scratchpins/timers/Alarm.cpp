/*
 * Alarm.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Dad
 */

#include "Alarm.h"

#include <stddef.h>

namespace timers {

Alarm::Alarm()
: callback(NULL)
{
}

Alarm::~Alarm() {
}

Alarm& Alarm::attachInterrupt(Callback* callbackIn) {
	callback = callbackIn;
	return *this;
}

Alarm& Alarm::detachInterrupt() {
	stop();
	callback = NULL;
	return *this;
}

Alarm& Alarm::setPeriod(unsigned int periodMs) {
	// Convert period in microseconds to frequency in Hz
	double frequency = 1000000.0 / periodMs;
	setFrequency(frequency);
	return *this;
}

void Alarm::doCallback() {
	callback->loop(*this);
}

void Alarm::Callback::loop(Alarm& alarm) {
}


class Alarm1 : public Alarm {
public:
	Alarm1(bool channelA);
	virtual ~Alarm1();
	virtual Alarm& start();
	virtual Alarm& stop();
	virtual Alarm& setFrequency(double frequencyHz);
	virtual double getFrequency() const;

	bool channelA;

private:
	static bool isInited;
	static void init();
};

bool Alarm1::isInited = false;
void Alarm1::init() {
	if (!isInited) {
	    // initialize Timer1*/
	    cli();          // disable global interrupts

	    TCCR1A = 0;     // set entire TCCR1A register to 0
	    TCCR1B = 0;     // same for TCCR1B

	    // set compare match register to desired timer count:
	    OCR1A = 32000;
	    OCR1B = 32000;
	    // turn on CTC mode:
	    TCCR1B |= (1 << WGM12);
	    // Set CS10 and CS12 bits for 1024 prescaler:
	    TCCR1B |= (1 << CS10);
	    TCCR1B |= (1 << CS12);
	    // enable global interrupts:
	    sei();
	}
}


Alarm1::Alarm1(bool channelAIn)
: channelA(channelAIn)
{
}

Alarm1::~Alarm1() {
}

Alarm& Alarm1::start() {
	if (channelA) {
		TIMSK1 = TIMSK1 | (1 << OCIE1A);
	} else {
		TIMSK1 = TIMSK1 | (1 << OCIE1B);
	}
	return *this;
}

Alarm& Alarm1::stop() {
	if (channelA) {
		TIMSK1 = TIMSK1 & ~(1 << OCIE1A);
	} else {
		TIMSK1 = TIMSK1 & ~(1 << OCIE1B);
	}
	return *this;
}

Alarm& Alarm1::setFrequency(double frequencyHz) {

	const byte prescalarValueMask = ~((1<<CS10) | (1<<CS11) | (1<<CS12));
	struct {
		int divisor;
		byte symbol;
	} scalars[] = {
			{ 1, (1<<CS10) },
			{ 8, (1<<CS11) },
			{ 64, (1<<CS10) | (1<<CS11) },
			{ 256, (1<<CS12) },
			{ 1024, (1<<CS12) | (1<<CS10) },
	};

	long desiredTicks = 16000000L / frequencyHz;
	unsigned long bestError = -1;
	byte ndx = 0;
	for (byte i = 0; i < 5; i++) {
		long actualTicks = 16000000L / scalars[i].divisor;
		unsigned long error = abs(desiredTicks - actualTicks);
		if (error < bestError) {
			bestError = error;
			ndx = i;
		}
	}
	TCCR1B = (TCCR1B & prescalarValueMask) | scalars[ndx].symbol;
	if (channelA) {
		OCR1A = bestError;
	} else {
		OCR1B = bestError;
	}
	return *this;
}

} /* namespace timers */

