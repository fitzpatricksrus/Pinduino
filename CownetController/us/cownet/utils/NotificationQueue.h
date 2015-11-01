/*
 * NotificationQueue.h
 *
 *  Created on: Oct 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_UTILS_NOTIFICATIONQUEUE_H_
#define US_COWNET_UTILS_NOTIFICATIONQUEUE_H_

#include "Listener.h"
#include "Notifier.h"
#include "Map.h"

namespace us_cownet_utils {

class NotificationQueue {
public:
	NotificationQueue();
	virtual ~NotificationQueue();

	virtual void addNotifier(int tag, BaseNotifier* notifier);
	virtual BaseNotifier* notifierFor(int tag);
	virtual void dispatchNotifications();

private:
	static const int maxNotifierTypes = 20;
	typedef Map<int, BaseNotifier*, maxNotifierTypes> NotifierListType;

	NotifierListType notifiers;
};

} /* namespace us_cownet_utils */

#endif /* US_COWNET_UTILS_NOTIFICATIONQUEUE_H_ */
