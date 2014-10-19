/*
 * TimerTest.h
 *
 *  Created on: Oct 18, 2014
 *      Author: Dad
 */

#ifndef TIMERTEST_H_
#define TIMERTEST_H_

#include "../../Tests/TestClass.h"
namespace scheduler {
namespace tests {

class TimerTest : public Tests::TestClass {
public:
	TimerTest();
	virtual ~TimerTest();
	virtual void setup();
	virtual void loop();
	void togglePins();

	static TimerTest TEST;
};

} /* namespace scheduler_test */
}

#endif /* TIMERTEST_H_ */
