/*
 * LampController.h
 *
 *  Created on: Jan 2, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_CONTROLLERS_LAMPCONTROLLER_H_
#define US_COWNET_LAMPS_CONTROLLERS_LAMPCONTROLLER_H_

#include "../patterns/UniversalLampPattern.h"

namespace us_cownet_lamps_controllers {

using us_cownet_lamps_patterns::UniversalLampPattern;

class LampController {
public:
	LampController();
	virtual ~LampController();

	virtual void setPattern(UniversalLampPattern* pattern) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_CONTROLLERS_LAMPCONTROLLER_H_ */
