/*
 * Max7221LampController.h
 *
 *  Created on: Jan 2, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_CONTROLLERS_MAX7221LAMPCONTROLLER_H_
#define US_COWNET_LAMPS_CONTROLLERS_MAX7221LAMPCONTROLLER_H_

#include "LampController.h"
#include <Max7221.h>

namespace us_cownet_lamps_controllers {

class Max7221LampController: public us_cownet_lamps_controllers::LampController {
public:
	Max7221LampController(int selectPin = 13);
	virtual ~Max7221LampController();

	virtual void setPattern(UniversalLampPattern* pattern);

private:
	Max7221 max7221;
	UniversalLampPattern* pattern;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_CONTROLLERS_MAX7221LAMPCONTROLLER_H_ */
