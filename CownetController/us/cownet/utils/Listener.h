/*
 * Listener.h
 *
 *  Created on: Oct 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_UTILS_LISTENER_H_
#define US_COWNET_UTILS_LISTENER_H_

namespace us_cownet_utils {

template <class T>
class Listener {
public:
	virtual ~Listener() {}
	virtual void handle(T param) = 0;
};

template <class C, class T>
class ListenerFor : public Listener<T> {
public:
	typedef void (C::*MemberFunction)();
	ListenerFor(C* instanceIn, MemberFunction memberFunctionIn)
	: instance(instanceIn), memberFunction(memberFunctionIn)
	{
	}
	virtual ~ListenerFor() {}
	virtual void handle(T param) {
		(instance->*memberFunction)(param);
	}

private:
	C* instance;
	MemberFunction memberFunction;
};

} /* namespace us_cownet_utils */

#endif /* US_COWNET_UTILS_LISTENER_H_ */
