/*
 * SimpleMatrixPins.h
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#ifndef PINS_SIMPLEMATRIXPINS_H_
#define PINS_SIMPLEMATRIXPINS_H_

#include "../pins/MatrixPattern.h"
#include "../pins/MatrixPins.h"
#include "../pins/OutputPins.h"
#include "../pins/SimplePinPattern.h"
#include "../timers/Timer.h"

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

#endif /* PINS_SIMPLEMATRIXPINS_H_ */





