/*
 * Scheduler.h
 *
 *  Created on: Oct 13, 2014
 *      Author: Dad
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include <Arduino.h>
//#include <WProgram.h>

namespace scheduler {

//provide a typedef for a void function pointer
typedef void (*function)();

typedef struct schedule_action_s {
	function action;
	unsigned long time;
	unsigned int delay;
	//assignment operator
	schedule_action_s& operator=(const schedule_action_s& rhs){
		action = rhs.action;
		time = rhs.time;
		delay = rhs.delay;
		return *this;
	}
	//boolean equality
	bool operator==(const schedule_action_s& rhs) const{
		return (action == rhs.action && time == rhs.time && delay == rhs.delay);
	}
}schedule_action;


class Scheduler {
	public:
		Scheduler();
		void update();
		void schedule(function userAction, unsigned int time);
	private:
		static const byte NUMBER_OF_SCHEDULED_ACTIONS = 10;
		void defragment();
		schedule_action action[NUMBER_OF_SCHEDULED_ACTIONS];
		byte currentSize;
};


} /* namespace SchedulerLib */

#endif /* SCHEDULER_H_ */
