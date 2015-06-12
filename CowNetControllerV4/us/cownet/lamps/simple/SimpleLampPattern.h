/*
 * SimpleLampPattern.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_SIMPLE_SIMPLELAMPPATTERN_H_
#define US_COWNET_LAMPS_SIMPLE_SIMPLELAMPPATTERN_H_

#include <Arduino.h>
#include "../LampPattern.h"

namespace us_cownet_lamps_simple {

using namespace us_cownet_lamps;

class SimpleLampPattern : public LampPattern {
public:
	SimpleLampPattern();
	SimpleLampPattern(byte pattern[], byte colCount);
	virtual ~SimpleLampPattern();

	virtual byte* getPattern();
	virtual void setPattern(byte pattern[], byte colCount);
	virtual bool getLamp(int col, int row);
	virtual void setLamp(int col, int row, bool on);

	virtual byte getColCount();

	static SimpleLampPattern& ALL_OFF;

private:
	byte* pattern;
	byte colCount;
};

} /* namespace us_cownet_lamps_simple */

#endif /* US_COWNET_LAMPS_SIMPLE_SIMPLELAMPPATTERN_H_ */
