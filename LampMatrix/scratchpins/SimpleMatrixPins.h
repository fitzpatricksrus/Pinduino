/*
 * SimpleMatrixPins.h
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#ifndef SCRATCHPINS_SIMPLEMATRIXPINS_H_
#define SCRATCHPINS_SIMPLEMATRIXPINS_H_

#include "MatrixPins.h"
#include "MatrixPattern.h"
#include "SimplePinPattern.h"
#include "OutputPins.h"
#include "timers/Timer.h"

namespace pins {

class SimpleMatrixPins: public MatrixPins, timers::Timer::Callback {
public:
	SimpleMatrixPins(OutputPins* pins);
	virtual ~SimpleMatrixPins();
	virtual void initPins();
    virtual void setPattern(MatrixPattern* pattern);
    virtual byte getCurrentColumn();
    virtual void setCurrentColumn(byte column);
    virtual void latch();

	virtual void loop();

private:
	MatrixPattern* pattern;
	byte currentColumn;
	SimplePinPattern currentColumnPattern;
	OutputPins* pins;
};

} /* namespace pins */

#endif /* SCRATCHPINS_SIMPLEMATRIXPINS_H_ */





