/*
 * Listener.h
 *
 *  Created on: Oct 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_UTILS_LISTENER_H_
#define US_COWNET_UTILS_LISTENER_H_

namespace us_cownet_utils {

template <class ParamClass>
class Listener {
public:
	virtual ~Listener() {}
	virtual void handle(ParamClass param) = 0;
};

template <class ListenerClass, class ParamClass>
class ListenerFor : public Listener<ParamClass> {
public:
	typedef void (ListenerClass::*MemberFunction)(ParamClass param);
	ListenerFor(ListenerClass* instanceIn, MemberFunction memberFunctionIn)
	: instance(instanceIn), memberFunction(memberFunctionIn)
	{
	}
	virtual ~ListenerFor() {}
	virtual void handle(ParamClass param) {
		(instance->*memberFunction)(param);
	}

private:
	ListenerClass* instance;
	MemberFunction memberFunction;
};

} /* namespace us_cownet_utils */

#endif /* US_COWNET_UTILS_LISTENER_H_ */
