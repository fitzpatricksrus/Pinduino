/*
 * PinballOutputController.h
 *
 *  Created on: Oct 9, 2015
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

	enum Register {
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
		REGISTER_COUNT
	};

	virtual int getColumnCount() = 0;

	/* Write to the specified data input source */
	virtual void write(Register signal, byte value) = 0;

	virtual void writeRow(byte value) {
		write(LAMP_ROW, (byte)value);
	}

	virtual void writeCol(byte value) {
		write(LAMP_COL, value);
	}
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_PINBALLOUTPUTCONTROLLER_H_ */
