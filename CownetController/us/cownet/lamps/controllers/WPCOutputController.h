/*
 * WPCOutputController.h
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#ifndef US_COWNET_LAMPS_CONTROLLERS_WPCOUTPUTCONTROLLER_H_
#define US_COWNET_LAMPS_CONTROLLERS_WPCOUTPUTCONTROLLER_H_

#include "../PinballOutputController.h"

namespace us_cownet_lamps_controllers {

using namespace us_cownet_lamps;

class WPCOutputController : public PinballOutputController {
public:
	WPCOutputController(int dataPinsIn[], int signalPinsIn[]);
	virtual ~WPCOutputController();

	virtual int getColumnCount();
	virtual void write(Register signal, byte value);

private:
	int* dataPins;
	int* signalPins;
};

} /* namespace us_cownet_lamps_wpc */

#endif /* WPCOUTPUTCONTROLLER_H_ */
