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
		virtual void setup() = 0;
		virtual void run() = 0;
	};
	enum PrescalarX { PS1 = (1 << CS10), PS8 = (1 << CS11), PS64 = (1 << CS10) | (1 << CS11),
		PS256 = (1 << CS12), PS1024 = (1 << CS10) | (1 << CS12) };
	enum TCCR1AMode = { 
		OFF_MASK = ~((1 << COM1A0) | (1 << COM1A1) | (1 << PWM10) | (1 << PWM11)),
		COMPARE_TOGGLE = (1 << COM1A0), 
		COMPARE_CLEAR = (1 << COM1A1), 
		COMPARE_SET = (1 << COM1A0) | (1 << COM1A1),
		PWM8BIT = (1 << PWM10),
		PWM9BIT = (1 << PWM11),
		PWM10BIT = (1 << PWM10) | (1 << PWM11),	
		STOP_TIMER_MASK = ~((1 << CS10) | (1 << CS11) | (1 << CS12)),
	};
	enum TCCR1BMode = {
		INPUT_CAPTURE_NOISE_CANCELING_ON = (1 << ICNC1),
		IMPUT_CAPTURE_ON_RISING_EDGE = (1 << ICES1),
		CLEAR_TIMER_ON_MATCH = (1 << CTC1),
		NO_PRESCALAR = (1 << CS10),
		PRESCALAR_8 = (1 << CS11),
		PRESCALAR_64 = (1 << CS10) ,
		PRESCALAR_256 = (1 << CS11),
		PRESCALAR_1024 = (1 << CS11),
	};

	virtual ~Timer();
	Timer::Callback* getCallback() const;
	virtual void setCallback(Timer::Callback* callback, int ticks);
	virtual void resetTimer() = 0;
	virtual void setPrescalar(Prescalar scalar) = 0;
	virtual int getTicks() const = 0;
	virtual void setTicks(int ticks) = 0;
	
	enum Prescalar { TIMER_OFF, PS1, PS8, PS64, PS256, PS1024, 
		PSExternalFalling, PSExternalRising };
	virtual void setPrescalar(Prescalar p) = 0;

	
	
	static Timer& TIMER1;


protected:
	Timer();

private:
	Timer::Callback* callback;
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
