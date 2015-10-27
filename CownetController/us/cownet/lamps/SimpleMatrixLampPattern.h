/*
 * SimpleMatrixLampPattern.h
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#ifndef US_COWNET_LAMPS_SIMPLEMATRIXLAMPPATTERN_H_
#define US_COWNET_LAMPS_SIMPLEMATRIXLAMPPATTERN_H_

#include "MatrixLampPattern.h"

namespace us_cownet_lamps {

class SimpleMatrixLampPattern : public MatrixLampPattern {
public:
	SimpleMatrixLampPattern(int* patternIn, int columnCountIn);

	virtual ~SimpleMatrixLampPattern();

	virtual int* getPattern();

	virtual void setPattern(int* newPattern);

	virtual byte getColumn(int col);

	virtual bool getLamp(int x, int y);

	virtual void setLamp(int col, int row, boolean on);

	virtual int getColCount();

	virtual void attached();

	virtual void endOfMatrixSync();

	virtual bool isDone();

	virtual void reset();

	virtual void detached();

//	virtual void allOn();

//	virtual void allOff();

//	virtual void unionPattern(LampPattern* other);

//	virtual void difference(LampPattern* other);

private:
	int* pattern;
};

} /* namespace us_cownet_lamps */

#endif /* SIMPLEMATRIXLAMPPATTERN_H_ */
