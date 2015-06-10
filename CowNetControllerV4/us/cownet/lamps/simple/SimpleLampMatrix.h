#ifndef US_COWNET_LAMPS_SIMPLELAMPMATRIX_H_
#define US_COWNET_LAMPS_SIMPLELAMPMATRIX_H_

#include <Arduino.h>
#include "../LampMatrix.h"
#include "../PinballOutputController.h"
#include "../../timers/TimerUtil.h"

namespace us_cownet_lamps_simple {
	
using namespace us_cownet_lamps;
using namespace us_cownet_timers;

class SimpleLampMatrix : public LampMatrix {
public:
	SimpleLampMatrix(PinballOutputController* controller, long micros);
	virtual ~SimpleLampMatrix();
	virtual LampPattern* getDisplayedPattern();
	virtual LampPattern* getPattern();
	virtual void setPattern(LampPattern* lamps);
	virtual void setSyncCallback(Callback* callbackIn);

private:
	void tock();
	CallbackTo<SimpleLampMatrix> thisCallback;

	PinballOutputController* controller;
	long micros;
	int currentColumn;
	LampPattern* currentPattern;
	LampPattern* nextPattern;
	Callback* callback;
};

} /* namespace us_cownet_lamps_simple */

#endif /* US_COWNET_LAMPS_SIMPLELAMPMATRIX_H_ */
