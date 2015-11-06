/*
 * Notifier.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: Dad
 */

#include "Notifier.h"

namespace us_cownet_utils {

BaseNotifier::BaseNotifier() {
}

BaseNotifier::~BaseNotifier() {
}

void BaseNotifier::dispatchNotifications() {
}

void BaseNotifier::dispatchAllNotifications() {
	for (int i = 0; i < notifiers.size(); i++) {
		notifiers[i]->dispatchNotifications();
	}
}


} /* namespace us_cownet_utils */

