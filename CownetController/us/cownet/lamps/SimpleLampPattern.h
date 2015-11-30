/*
 * SimpleLampPattern.h
 *
 *  Created on: Oct 23, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_SIMPLELAMPPATTERN_H_
#define US_COWNET_LAMPS_SIMPLELAMPPATTERN_H_

#include "MatrixLampPattern.h"

namespace us_cownet_lamps {

class SimpleLampPattern: public LampPattern {
public:
	SimpleLampPattern();

	SimpleLampPattern(int* patternIn, int columnCountIn);

	template <int columnCountIn>
	SimpleLampPattern(int (&patternIn)[columnCountIn])
	: pattern(patternIn), columnCount(columnCountIn)
	{
	}

	virtual ~SimpleLampPattern();

	virtual int* getPattern();

	virtual void setPattern(int* newPattern, int columnCountIn);

	template <int columnCountIn>
	void setPattern(int (&newPattern)[columnCountIn])
	{
		pattern = newPattern;
		columnCount = columnCountIn;
	}

	virtual byte getColumn(int col);

	virtual int getLampCount();

	virtual bool getLamp(int index);

	virtual void setLamp(int ndx, boolean on);

	virtual void attached();

	virtual void endOfMatrixSync();

	virtual bool isDone();

	virtual void reset();

	virtual void detached();

	virtual void allOn();

	virtual void allOff();

	virtual void unionPattern(LampPattern* other);

	virtual void differencePattern(LampPattern* other);

private:
	int columnCount;
	int* pattern;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_SIMPLELAMPPATTERN_H_ */

