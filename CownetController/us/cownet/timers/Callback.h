/*
 * Callback.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TIMERS_CALLBACK_H_
#define US_COWNET_TIMERS_CALLBACK_H_

namespace us_cownet_timers {

class Callback {
public:
	Callback();
	virtual ~Callback();

	virtual void call();
};

template <class T>
class CallbackFor : public Callback {
public:
	typedef void (T::*MemberFunction)();
	CallbackFor(T* instance, MemberFunction memberFunction);
	virtual void call();

private:
	T* instance;
	MemberFunction memberFunction;
};

template<class T>
inline CallbackFor<T>::CallbackFor(T* instanceIn, MemberFunction memberFunctionIn)
: instance(instanceIn), memberFunction(memberFunctionIn)
{
}

template<class T>
inline void CallbackFor<T>::call() {
	(instance->*memberFunction)();
}

} /* namespace us_cownet_timers */

#endif /* US_COWNET_TIMERS_CALLBACK_H_ */
