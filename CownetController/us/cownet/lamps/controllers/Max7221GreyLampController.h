/*
 * Max7221GreyLampController.h
 *
 *  Created on: Jan 4, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_CONTROLLERS_MAX7221GREYLAMPCONTROLLER_H_
#define US_COWNET_LAMPS_CONTROLLERS_MAX7221GREYLAMPCONTROLLER_H_

#include "LampController.h"

#include <Max7221.h>

#include "../../timers/Callback.h"
using us_cownet_timers::CallbackFor;

namespace us_cownet_lamps_controllers {

class Max7221GreyLampController: public LampController {
public:
	Max7221GreyLampController(int selectPin = 13, long refreshFrequencyIn = 0);
	virtual ~Max7221GreyLampController();

	virtual void setPattern(UniversalLampPattern* pattern);

private:
	void tock();

	Max7221 max7221;
	UniversalLampPattern* pattern;
	long refreshFrequency;
	CallbackFor<Max7221GreyLampController> tockCallback;
	byte lampPhase;
};

} /* namespace us_cownet_lamps_controllers */

#endif /* US_COWNET_LAMPS_CONTROLLERS_MAX7221GREYLAMPCONTROLLER_H_ */
