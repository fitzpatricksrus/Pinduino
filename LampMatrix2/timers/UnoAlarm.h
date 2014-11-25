/*
 * UnoAlarm.h
 *
 *  Created on: Nov 22, 2014
 *      Author: Dad
 */

#ifndef TIMERS_UNOALARM_H_
#define TIMERS_UNOALARM_H_

#include "Alarm.h"

namespace timers {

class UnoAlarm: public Alarm {
public:
	virtual ~UnoAlarm();
//	virtual void attachInterrupt(Callback* callback);
//	virtual void detachInterrupt();
//	virtual void start() = 0;
//	virtual void stop() = 0;
	virtual void setFrequency(double frequencyHz);
//	virtual void setPeriod(unsigned long periodUs);

//	static Alarm& alarm0a;
//	static Alarm& alarm0b;
	static Alarm& alarm1a;	//16 bit timer
	static Alarm& alarm1b;
	static Alarm& alarm2a;	//8 bit timer
	static Alarm& alarm2b;

	typedef struct {
		unsigned int scalar;
		byte mask;
	} PrescalarDef;

protected:
	UnoAlarm(const PrescalarDef* scalars, bool isTimerA);

	virtual void setTicks(int ticks) = 0;
	virtual void setScalar(byte andMask, byte orMask) = 0;

	const PrescalarDef* scalars;
	bool isTimerA;
};

} /* namespace timers */

#endif /* TIMERS_UNOALARM_H_ */
