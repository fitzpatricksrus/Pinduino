/*
 * WPCLampMatrix.h
 *
 *  Created on: Jan 25, 2015
 *      Author: Dad
 */

#ifndef WPCLAMPMATRIX_H_
#define WPCLAMPMATRIX_H_

#include "LampMatrix.h"

/*
 * The WPC lamp matrix is driven by a row select pin, a column select pin, and
 * a shared 8 bit data bus.  To turn a set of rows on, 8 bits of data is put on the
 * data bus, low signifying that the row should be ENABLED.  The row select pin is then
 * toggled from low to high to latch the data.  The setup for the columns is the same.
 * data is put on the data bus, low signifying the column is on, and the rising transition
 * on the column select pin latches the data.  The columns have a single master output
 * control (OC) line that turns the enables the output of puts them into a high impedance state.
 * When OC is low, the output are high impedance.
 */
class WPCLampMatrix : public LampMatrix {
public:
	WPCLampMatrix(byte colSelectPin, byte rowSelectPin, byte firstDataPin);
	virtual ~WPCLampMatrix();

	virtual void init();
	virtual void setColumn(byte column, byte values);
	virtual void setColumn(byte column);
	virtual void setRows(byte rows);

private:
	void writeDataPins(byte value);

	byte colSelectPin;
	byte rowSelectPin;
	byte firstDataPin;
	bool isInited;

};

#endif /* WPCLAMPMATRIX_H_ */
