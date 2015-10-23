/*
 * Test.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#include "Test.h"

namespace us_cownet_testing {

Test::Test() {
}

Test::~Test() {
}

void Test::setup() {
}

void Test::loop() {
}

bool Test::isDone() {
	return false;
}

void Test::execute() {
	execute(0);
}

void Test::execute(long ticksPerLoop) {
	setup();

	PeriodicEvent loopTick = PeriodicEvent::forTime(ticksPerLoop);
	while (!isDone()) {
		if (loopTick.isTime()) {
			loop();
		}
	}
}

} /* namespace us_cownet_testing */
