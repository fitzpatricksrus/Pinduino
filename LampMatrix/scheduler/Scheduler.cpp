/*
 * Scheduler.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: Dad
 */

#include "Scheduler.h"

namespace scheduler {

Scheduler::Scheduler(){
	action[0].action = NULL;
	action[0].delay = 65535;
	action[0].time = 0;
	currentSize = 0;
}

//Check to see if it's time to call any of the functions
void Scheduler::update(){
	//flush/update all
	for (byte i=0; i<currentSize; i++){
		//it is time to call the function associated with action[i]
		if ((millis() - action[i].time) > action[i].delay){
			action[i].action(); //call function
			//this was the last action in queue
			if (i==0 && currentSize==1){ currentSize=0; }
			//this is the second action of two possible, only one left
			else if (i==1 && currentSize==2){ currentSize=1; }
			//the last action has executed, cut it off
			else if (i+1==currentSize){
				currentSize--;
			}
			//all other elements
			else if (i+1<currentSize){
				action[i] = action[i+1];
				defragment(); //get rid of the two copies in memory
			}
		}
	}
}

//Schedule a functioncall in 'time' milliseconds.
void Scheduler::schedule(function userAction, unsigned int time){
	if (currentSize<NUMBER_OF_SCHEDULED_ACTIONS){
		action[currentSize].action = userAction;
		action[currentSize].delay = time;
		action[currentSize].time = millis();
		currentSize++;
	}
}

//Removes all redundant actions from memory
void Scheduler::defragment(){
	byte defrag=0;
	for (byte i=0; i<currentSize; i++){
		if(i+1 < currentSize && action[i] == action[i+1]){
			defrag=i+1;
			while (defrag+1 < currentSize){
				action[defrag] = action[defrag+1];
				defrag++;
			}
			currentSize--;
		}
	}
}

}


