/*
 * Notifier.h
 *
 *  Created on: Oct 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_UTILS_NOTIFIER_H_
#define US_COWNET_UTILS_NOTIFIER_H_

#include "List.h"

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

template <class T, int maxQueueSize, int maxListeners>
class Notifier {
public:
	Notifier();
	virtual ~Notifier();

	virtual void addListener(Listener<T>* listener);
	virtual void removeListener(Listener<T>* listener);

	virtual void notify(T param);
	virtual void dispatchNotifications();

private:
	List<Listener<T>, maxListeners> listeners;
	List<T, maxQueueSize> queue;
};

template<class T, int maxQueueSize, int maxListeners>
inline Notifier<T, maxQueueSize, maxListeners>::Notifier()
: listeners(), queue()
{
}

template<class T, int maxQueueSize, int maxListeners>
inline Notifier<T, maxQueueSize, maxListeners>::~Notifier() {
}

template<class T, int maxQueueSize, int maxListeners>
inline void Notifier<T, maxQueueSize, maxListeners>::addListener(Listener<T>* listener) {
	listeners.add(listener);
}

template<class T, int maxQueueSize, int maxListeners>
inline void Notifier<T, maxQueueSize, maxListeners>::removeListener(Listener<T>* listener) {
	listeners.remove(listener);
}

template<class T, int maxQueueSize, int maxListeners>
inline void Notifier<T, maxQueueSize, maxListeners>::notify(T param) {
	for (int e = 0; e < queue.size(); e++) {
		T event = queue[e];
		for (int l = 0; l < listeners.size(); l++) {
			listeners[l]->handle(event);
		}
	}
	queue.clear();
}

template<class T, int maxQueueSize, int maxListeners>
inline void Notifier<T, maxQueueSize, maxListeners>::dispatchNotifications() {
}

} /* namespace us_cownet_utils */

#endif /* US_COWNET_UTILS_NOTIFIER_H_ */
