/*
 * NotificationQueue.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: Dad
 */

#include "NotificationQueue.h"
#include <stdlib.h>
#include "List.h"

namespace us_cownet_utils {

NotificationQueue::NotificationQueue()
: notifiers(0, NULL)
{
}

NotificationQueue::~NotificationQueue() {
}

void NotificationQueue::addNotifier(int tag, BaseNotifier* notifier) {
	notifiers.put(tag, notifier);
}

BaseNotifier* NotificationQueue::notifierFor(int tag) {
	return notifiers.get(tag);
}

void NotificationQueue::dispatchNotifications() {
	for (int i = 0; i < notifiers.valueList.size(); i++) {
		notifiers.valueList[i]->dispatchNotifications();
	}
}

static NotificationQueue REAL_INSTANCE;
NotificationQueue& NotificationQueue::INSTANCE = REAL_INSTANCE;


} /* namespace us_cownet_utils */
