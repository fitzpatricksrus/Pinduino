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
	SimpleMatrixLampPattern();

	SimpleMatrixLampPattern(int* patternIn, int columnCountIn);

	virtual ~SimpleMatrixLampPattern();

	virtual int* getPattern();

	virtual void setPattern(int* newPattern, int columnCountIn);

	virtual byte getColumn(int col);

	virtual bool getLamp(int col, int row);

	virtual void setLamp(int col, int row, bool on);

	virtual int getColCount();

private:
	int* pattern;
	int columnCount;
};

} /* namespace us_cownet_lamps */

#endif /* SIMPLEMATRIXLAMPPATTERN_H_ */
