/*
 * BAMOutputMatrix.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Dad
 */

#ifndef BAMOUTPUTMATRIX_H_
#define BAMOUTPUTMATRIX_H_

#include "../scheduler/Timer.h"
#include "OutputPins.h"

class BAMOutputMatrix : private scheduler::Timer::Callback {
public:
	BAMOutputMatrix(scheduler::Timer* timer, OutputPins* pins, byte columnCount);
	virtual ~BAMOutputMatrix();
	virtual byte getRowCount() const;
	virtual byte getColumnCount() const;
	virtual byte getPin(byte col, byte row) const;
	virtual void setPin(byte col, byte row, byte pinValue);
	virtual void latch();

private:
	virtual void setup();
	virtual void loop();

	OutputPins* pins;
	byte** values;
	byte columnCount;
	byte bitInCycle;
	byte colInCycle;
	scheduler::Timer* timer;
};

#endif /* BAMOUTPUTMATRIX_H_ */
