/*
 * Notifier.h
 *
 *  Created on: Oct 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_UTILS_NOTIFIER_H_
#define US_COWNET_UTILS_NOTIFIER_H_

#include "List.h"
#include "Listener.h"

namespace us_cownet_utils {

class BaseNotifier {
public:
	BaseNotifier();
	virtual ~BaseNotifier();
	virtual void dispatchNotifications();
};

template <class T, int maxQueueSize, int maxListeners>
class Notifier : public BaseNotifier {
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
