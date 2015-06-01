/*
 * WpcOutputController.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_WPC_WPCOUTPUTCONTROLLER_H_
#define US_COWNET_LAMPS_WPC_WPCOUTPUTCONTROLLER_H_

#include <Arduino.h>
#include "PinballOutputController.h"

namespace us_cownet_lamps {

class WpcOutputController {
public:
	WpcOutputController();
	virtual ~WpcOutputController();

	virtual void write(PinballOutputController::Register signal, byte value);


private:
	byte dataPin[8];
	byte signalPin[PinballOutputController::SIGNAL_COUNT];

};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_WPC_WPCOUTPUTCONTROLLER_H_ */
