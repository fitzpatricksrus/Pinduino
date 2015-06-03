/*
 * SimpleGreyscaleLampPattern.h
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#ifndef SIMPLEGREYSCALELAMPPATTERN_H_
#define SIMPLEGREYSCALELAMPPATTERN_H_

#include <Arduino.h>

namespace us_cownet_lamps_simple {

class SimpleGreyscaleLampPattern {
public:
	SimpleGreyscaleLampPattern();
	virtual ~SimpleGreyscaleLampPattern();

	virtual byte** getPattern();
	virtual void setPattern(byte** pattern);
	virtual byte getLamp(int col, int row);
	virtual void setLamp(int col, int row, byte value);

private:
	byte** pattern;
};

} /* namespace us_cownet_lamps_simple */

#endif /* SIMPLEGREYSCALELAMPPATTERN_H_ */
