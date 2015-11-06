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

	static void dispatchAllNotifications();

protected:
	static const int maxNotifierTypes = 20;
	typedef List<BaseNotifier*, maxNotifierTypes> NotifierListType;

	static NotifierListType notifiers;
};

template <class T, int maxQueueSize, int maxListeners>
class Notifier : public BaseNotifier {
public:
	Notifier();
	virtual ~Notifier();

	virtual void addListener(Listener<T>* listener);
	virtual void removeListener(Listener<T>* listener);

	virtual void queueNotification(T param);
	virtual void dispatchNotifications();

private:
	List<Listener<T>, maxListeners> listeners;
	List<T, maxQueueSize> queue;
};

template<class T, int maxQueueSize, int maxListeners>
inline Notifier<T, maxQueueSize, maxListeners>::Notifier()
: listeners(), queue()
{
	notifiers.add(this);
}

template<class T, int maxQueueSize, int maxListeners>
inline Notifier<T, maxQueueSize, maxListeners>::~Notifier() {
	notifiers.remove(this);
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
inline void Notifier<T, maxQueueSize, maxListeners>::queueNotification(T param) {
	queue.add(param);
}

template<class T, int maxQueueSize, int maxListeners>
inline void Notifier<T, maxQueueSize, maxListeners>::dispatchNotifications() {
	for (int e = 0; e < queue.size(); e++) {
		T event = queue[e];
		for (int l = 0; l < listeners.size(); l++) {
			listeners[l]->handle(event);
		}
	}
	queue.clear();
}

} /* namespace us_cownet_utils */

#endif /* US_COWNET_UTILS_NOTIFIER_H_ */
