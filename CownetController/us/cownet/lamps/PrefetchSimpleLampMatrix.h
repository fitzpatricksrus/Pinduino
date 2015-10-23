/*
 * PrefetchSimpleLampMatrix.h
 *
 *  Created on: Oct 22, 2015
 *      Author: jfitzpatrick
 */

#ifndef PREFETCHSIMPLELAMPMATRIX_H_
#define PREFETCHSIMPLELAMPMATRIX_H_

#include "LampMatrix.h"
#include "LampPattern.h"
#include "PinballOutputController.h"
#include "../timers/Callback.h"
#include "../timers/TimerUtil.h"

namespace us_cownet_lamps {

using namespace us_cownet_timers;

class PrefetchSimpleLampMatrix : public LampMatrix {
public:
	PrefetchSimpleLampMatrix(PinballOutputController* controller, long ticks);
	virtual ~PrefetchSimpleLampMatrix();

	LampPattern* getDisplayedPattern();
	LampPattern* getPattern();
	void setPattern(LampPattern* lamps);
	void tock();
	void setSyncCallback(Callback* callback);

protected:
	byte internalGetColumn(LampPattern* pattern, int columnNumber);
	void internalSetPattern(LampPattern* newPattern);
	void internalEndOfMatrixSync(LampPattern* pattern);

private:
	PinballOutputController* controller;
	long ticks;
	int currentColumn;
	LampPattern* nextPattern;
	Callback* syncCallback;
	LampPattern* attachedPattern;
	CallbackFor<PrefetchSimpleLampMatrix> thisCallback;
	byte prefetchedColumnValue;
};

} /* namespace us_cownet_lamps */

#endif /* PREFETCHSIMPLELAMPMATRIX_H_ */
