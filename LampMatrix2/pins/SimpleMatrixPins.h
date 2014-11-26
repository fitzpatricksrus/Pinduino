/*
 * SimpleMatrixPins.h
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#ifndef PINS_SIMPLEMATRIXPINS_H_
#define PINS_SIMPLEMATRIXPINS_H_

#include "MatrixPattern.h"
#include "MatrixPins.h"
#include "OutputPins.h"
#include "SimplePinPattern.h"

namespace pins {

class SimpleMatrixPins: public MatrixPins {
public:
	SimpleMatrixPins(OutputPins* colPins, OutputPins* rowPins);
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
	OutputPins* rowPins;
	OutputPins* colPins;
};

} /* namespace pins */

#endif /* PINS_SIMPLEMATRIXPINS_H_ */





