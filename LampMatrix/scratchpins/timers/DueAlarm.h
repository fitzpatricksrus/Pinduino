/*
  DueTimer.h - DueTimer header file, definition of methods and attributes...
  For instructions, go to https://github.com/ivanseidel/DueTimer

  Created by Ivan Seidel Gomes, March, 2013.
  Modified by Philipp Klaus, June 2013.
  Released into the public domain.
*/

#ifdef __arm__

#ifndef DueTimer_h
#define DueTimer_h

#include "Arduino.h"
#include "Alarm.h"
#include <inttypes.h>

/*
	This fixes compatibility for Arduono Servo Library.
	Uncomment to make it compatible.

	Note that:
		+ Timers: 0,2,3,4,5 WILL NOT WORK, and will
				neither be accessible by Timer0,...
*/
// #define USING_SERVO_LIB	true

#ifdef USING_SERVO_LIB
	#warning "HEY! You have set flag USING_SERVO_LIB. Timer0, 2,3,4 and 5 are not available"
#endif


#define NUM_TIMERS  9

namespace timers {

class DueAlarm : public Alarm {
public:
	struct Timer
	{
		Tc *tc;
		uint32_t channel;
		IRQn_Type irq;
	};

	DueAlarm(unsigned short _timer);
	void start();
	void stop();
	void setFrequency(double frequency);
	void setPeriod(unsigned long microseconds);

	double getFrequency() const;
	long getPeriod() const;

	static DueAlarm& timer1;
	// Fix for compatibility with Servo library
	#ifndef USING_SERVO_LIB
	static DueAlarm& timer0;	// incompatible with Servo library
	static DueAlarm& timer2;	// incompatible with Servo library
	static DueAlarm& timer3;	// incompatible with Servo library
	static DueAlarm& timer4;	// incompatible with Servo library
	static DueAlarm& timer5;	// incompatible with Servo library
	#endif
	static DueAlarm& timer6;
	static DueAlarm& timer7;
	static DueAlarm& timer8;


protected:
	static uint8_t bestClock(double frequency, uint32_t& retRC);
	double frequency;
	// Represents the timer id (index for the array of Timer structs)
	const unsigned short timer;

	// Make Interrupt handlers friends, so they can use callbacks
	friend void TC0_Handler();
	friend void TC1_Handler();
	friend void TC2_Handler();
	friend void TC3_Handler();
	friend void TC4_Handler();
	friend void TC5_Handler();
	friend void TC6_Handler();
	friend void TC7_Handler();
	friend void TC8_Handler();
};


} // namespace timers

#endif

#else
	// error Oops! Trying to include DueAlarm on another device?
#endif
