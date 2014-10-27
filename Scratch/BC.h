/*
 * BC.h
 *
 *  Created on: Oct 25, 2014
 *      Author: Dad
 */

#ifndef BC_H_
#define BC_H_

#include "Timer.h"

class BC : public Timer::Callback {
public:
	virtual void setup();
	virtual void loop();

	static void doSetup();
	static void doLoop();
};

#endif /* BC_H_ */
