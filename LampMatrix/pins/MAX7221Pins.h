/*
 * MAX7221Pins.h
 *
 *  Created on: Nov 2, 2014
 *      Author: Dad
 */

#ifndef MAX7221PINS_H_
#define MAX7221PINS_H_

#include <Arduino.h>

class MAX7221Pins {
public:
	MAX7221Pins(byte slaveSelectPin_ST_CP = 10, byte clockPin_SH_CP = 13, byte dataPin_DS = 11);
	virtual ~MAX7221Pins();
	virtual void initPins();
	virtual byte getRowCount() const;
	virtual byte getColumnCount() const;
	virtual byte getPin(byte col, byte row) const;
	virtual void setPin(byte col, byte row, bool pinValue);
	virtual void latch();

private:
	void send7221Command(byte cmd, byte value);

	bool values[8][8];
	byte ST_CP_Pin;
	byte SH_CP_Pin;
	byte DS_Pin;
};

#endif /* MAX7221PINS_H_ */
