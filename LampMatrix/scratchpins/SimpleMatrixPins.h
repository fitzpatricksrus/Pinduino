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
#include "OutputPins.h"
#include "../scheduler/Timer.h"

namespace pins {

class SimpleMatrixPins: public MatrixPins, scheduler::Timer::Callback {
public:
	SimpleMatrixPins(scheduler::Timer* timer, OutputPins* pins);
	virtual ~SimpleMatrixPins();
	virtual void initPins();
    virtual void setPattern(MatrixPattern* pattern);
    virtual void latch();

private:
	virtual void setup();
	virtual void loop();

    scheduler::Timer* timer;
	MatrixPattern* pattern;
	byte currentColumn;
	OutputPins* pins;
};

} /* namespace pins */

#endif /* SCRATCHPINS_SIMPLEMATRIXPINS_H_ */





