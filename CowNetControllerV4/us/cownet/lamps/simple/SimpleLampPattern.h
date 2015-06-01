/*
 * SimpleLampPattern.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_SIMPLE_SIMPLELAMPPATTERN_H_
#define US_COWNET_LAMPS_SIMPLE_SIMPLELAMPPATTERN_H_

#include <Arduino.h>
#include "../LampPattern.h"xxxxxxxxxxxx

namespace us_cownet_lamps_simple {

using namespace us_cownet_lamps;

class SimpleLampPattern : public LampPattern {
public:
	SimpleLampPattern();
	virtual ~SimpleLampPattern();

	virtual byte* getPattern();
	virtual void setPattern(byte pattern[]);
	virtual bool getLamp(int col, int row);
	virtual void setLamp(int col, int row, bool on);

	static const SimpleLampPattern& ALL_OFF;

private:
	byte pattern[8];
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_SIMPLE_SIMPLELAMPPATTERN_H_ */
