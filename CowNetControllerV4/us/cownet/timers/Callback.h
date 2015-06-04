/*
 * Callback.h
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

namespace us_cownet_timers {

class Callback {
public:
	Callback();
	virtual ~Callback();
	virtual void call() = 0;
};

class CallbackFunction : public Callback {
public:
	CallbackFunction(void (*fn)()) {
		function = fn;
	}

	virtual void call() {
		(*function)();
	}

private:
	void (*function)();
};

template<class T> class CallbackTo : public Callback {
public:
	CallbackTo(T* instanceIn, void (T::*functionIn)()) {
		instance =  instanceIn;
		function = functionIn;
	}
	virtual void call() {
		(instance->*function)();
	}

private:
	T* instance;
	void (T::*function)();
};

} /* namespace us_cownet_timers */

#endif /* CALLBACK_H_ */
