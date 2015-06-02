#ifndef US_COWNET_LAMPS_SIMPLELAMPMATRIX_H_
#define US_COWNET_LAMPS_SIMPLELAMPMATRIX_H_

#include <Arduino.h>
#include "../LampMatrix.h"
#include "../PinballOutputController.h"

namespace us_cownet_lamps_simple {
	
using namespace us_cownet_lamps;

class SimpleLampMatrix : public LampMatrix {
public:
	SimpleLampMatrix(PinballOutputController* controller, long micros);
	virtual ~SimpleLampMatrix();
	virtual LampPattern* getDisplayedPattern();
	virtual LampPattern* getPattern();
	virtual void setPattern(LampPattern* lamps);
	virtual void setSyncCallback(Runnable* callback);
	
private:
	void tock();
	
	PinballOutputController* controller;
	long micros;
	int currentColumn;
	LampPattern* currentPattern;
	LampPattern* nextPattern;
	Runnable* callback;
};

} /* namespace us_cownet_lamps_simple */

#endif /* US_COWNET_LAMPS_SIMPLELAMPMATRIX_H_ */
