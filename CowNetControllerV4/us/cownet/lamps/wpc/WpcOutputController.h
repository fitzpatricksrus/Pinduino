/*
 * WpcOutputController.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_WPC_WPCOUTPUTCONTROLLER_H_
#define US_COWNET_LAMPS_WPC_WPCOUTPUTCONTROLLER_H_

#include <Arduino.h>
#include "../PinballOutputController.h"

namespace us_cownet_lamps_wpc {

using namespace us_cownet_lamps;

class WpcOutputController : public PinballOutputController {
public:
	WpcOutputController(byte* dataPinsIn, byte* signalPinsIn);
	virtual ~WpcOutputController();

	virtual void write(PinballOutputController::Register signal, byte value);

private:
	byte *dataPin;
	byte *signalPin;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_WPC_WPCOUTPUTCONTROLLER_H_ */
