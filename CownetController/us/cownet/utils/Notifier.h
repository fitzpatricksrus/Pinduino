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

template <class NoteParamClass, int maxQueueSize, int maxListeners>
class Notifier : public BaseNotifier {
public:
	Notifier();
	virtual ~Notifier();

	virtual void addListener(Listener<NoteParamClass>* listener);
	virtual void removeListener(Listener<NoteParamClass>* listener);

	virtual void queueNotification(NoteParamClass param);
	virtual void dispatchNotifications();

private:
	List<Listener<NoteParamClass>*, maxListeners> listeners;
	List<NoteParamClass, maxQueueSize> queue;
};

template<class NoteParamClass, int maxQueueSize, int maxListeners>
inline Notifier<NoteParamClass, maxQueueSize, maxListeners>::Notifier()
: listeners(), queue()
{
	notifiers.add(this);
}

template<class NoteParamClass, int maxQueueSize, int maxListeners>
inline Notifier<NoteParamClass, maxQueueSize, maxListeners>::~Notifier() {
	notifiers.remove(this);
}

template<class NoteParamClass, int maxQueueSize, int maxListeners>
inline void Notifier<NoteParamClass, maxQueueSize, maxListeners>::addListener(Listener<NoteParamClass>* listener) {
	listeners.add(listener);
}

template<class NoteParamClass, int maxQueueSize, int maxListeners>
inline void Notifier<NoteParamClass, maxQueueSize, maxListeners>::removeListener(Listener<NoteParamClass>* listener) {
	listeners.remove(listener);
	if (listeners.size() == 0) {
		queue.clear();
	}
}

template<class NoteParamClass, int maxQueueSize, int maxListeners>
inline void Notifier<NoteParamClass, maxQueueSize, maxListeners>::queueNotification(NoteParamClass param) {
	if (listeners.size() > 0) {
		queue.add(param);
	}
}

template<class NoteParamClass, int maxQueueSize, int maxListeners>
inline void Notifier<NoteParamClass, maxQueueSize, maxListeners>::dispatchNotifications() {
	for (int e = 0; e < queue.size(); e++) {
		NoteParamClass event = queue[e];
		for (int l = 0; l < listeners.size(); l++) {
			listeners[l]->handle(event);
		}
	}
	queue.clear();
}

} /* namespace us_cownet_utils */

#endif /* US_COWNET_UTILS_NOTIFIER_H_ */
