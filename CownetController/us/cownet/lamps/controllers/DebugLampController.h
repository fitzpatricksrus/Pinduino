/*
 * DebugLampController.h
 *
 *  Created on: Jan 10, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPCONTROLLER_H_
#define US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPCONTROLLER_H_

#include "LampController.h"

namespace us_cownet_lamps_controllers {

class DebugLampController: public LampController {
public:
	DebugLampController();
	virtual ~DebugLampController();

	virtual void setPattern(UniversalLampPattern* pattern);

private:
	UniversalLampPattern* pattern;
};

} /* namespace us_cownet_lamps_controllers */

#endif /* US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPCONTROLLER_H_ */
