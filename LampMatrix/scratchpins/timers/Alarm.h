/*
 * Alarm.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Dad
 */

#ifndef SCRATCHPINS_TIMERS_ALARM_H_
#define SCRATCHPINS_TIMERS_ALARM_H_

#include <Arduino.h>

namespace timers {

class Alarm {
public:
	class Callback {
	public:
		virtual void loop(Alarm& alarm);
	};

	Alarm();
	virtual ~Alarm();

	virtual void attachInterrupt(Callback* callback);
	virtual void detachInterrupt();
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void setFrequency(double frequencyHz) = 0;
	virtual void setPeriod(unsigned long periodUs) = 0;

	void doCallback();
protected:
	Callback* callback;
};

template <class T>
class AlarmCallback : public Alarm::Callback {
public:
	typedef void (T::*TCallback)();

	AlarmCallback(T* instance, TCallback callback);
	virtual ~AlarmCallback();
	virtual void loop(Alarm& alarm);
private:
	T* obj;
	TCallback callback;
};

template <class T>
AlarmCallback<T>::AlarmCallback(T* instanceIn, TCallback callbackIn)
: obj(instanceIn), callback(callbackIn)
{
}

template <class T>
AlarmCallback<T>::~AlarmCallback()
{
}

template <class T>
void AlarmCallback<T>::loop(Alarm& alarm) {
	obj->*TCallback(alarm);
}

} /* namespace timers */

#endif /* SCRATCHPINS_TIMERS_ALARM_H_ */
