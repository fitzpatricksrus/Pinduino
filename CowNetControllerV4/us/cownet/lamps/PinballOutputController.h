/*
 * PinballOutputController.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_PINBALLOUTPUTCONTROLLER_H_
#define US_COWNET_LAMPS_PINBALLOUTPUTCONTROLLER_H_

#include <Arduino.h>

namespace us_cownet_lamps {

class PinballOutputController {
public:
	PinballOutputController();
	virtual ~PinballOutputController();

	typedef enum Register {
		LAMP_ROW,
		LAMP_COL,
		//		SOL1,
		//		SOL2,
		//		SOL3,
		//		SOL4,
		//		TRIAC,
		//		SWITCH_ROW,
		//		SWITCH_COL,
		//		SWITCH_DEDICATED,
		SIGNAL_COUNT
	} Register;

	virtual void write(Register signal, byte value) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_PINBALLOUTPUTCONTROLLER_H_ */
