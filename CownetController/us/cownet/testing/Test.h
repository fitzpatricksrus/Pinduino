/*
 * Test.h
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#ifndef US_COWNET_TESTING_TEST_H_
#define US_COWNET_TESTING_TEST_H_

#include "../timers/TimerUtil.h"
#include "../timers/PeriodicEvent.h"

namespace us_cownet_testing {

using namespace us_cownet_timers;

class Test {
public:
	Test();
	virtual ~Test();

	virtual void setup();

	virtual void loop();

	virtual bool isDone();

	virtual void execute();

	virtual void execute(long ticksPerLoop);
};

} /* namespace us_cownet_testing */

#endif /* US_COWNET_TESTING_TEST_H_ */
