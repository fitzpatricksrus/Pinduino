#include "SimpleLampMatrix.h"

#include "SimpleLampPattern.h"

#include <Debug.h>

namespace us_cownet_lamps_simple {

using namespace us_cownet_timers;

SimpleLampMatrix::SimpleLampMatrix(PinballOutputController* controllerIn, long microsIn)
: thisCallback(this, &SimpleLampMatrix::tock), controller(controllerIn), micros(microsIn), currentColumn(0),
  currentPattern(NULL), nextPattern(NULL),
  callback(0) {
}

SimpleLampMatrix::~SimpleLampMatrix() {
}

LampPattern* SimpleLampMatrix::getDisplayedPattern() {
	return currentPattern;
}

LampPattern* SimpleLampMatrix::getPattern() {
	return nextPattern;
}

void SimpleLampMatrix::setPattern(LampPattern* lamps) {
	nextPattern = lamps;
	if (currentPattern == NULL && nextPattern != NULL) {
		Serial << "SimpleLampMatrix register callback" << endl;
		currentPattern = nextPattern;
		TimerUtil::INSTANCE.attachTimerCallback(&thisCallback, micros);
	} else if (currentPattern != NULL && nextPattern == NULL) {
		Serial << "SimpleLampMatrix DE-register callback" << endl;
		TimerUtil::INSTANCE.detachCallback(&thisCallback);
		currentPattern = NULL;
	}
}

void SimpleLampMatrix::setSyncCallback(Callback* callbackIn) {
	callback = callbackIn;
}

void SimpleLampMatrix::tock() {
	controller->write(PinballOutputController::LAMP_COL, (byte)0);
	controller->write(PinballOutputController::LAMP_ROW, currentPattern->getPattern()[currentColumn]);
	controller->write(PinballOutputController::LAMP_COL, (byte)(1 << currentColumn));
	currentColumn = (currentColumn + 1) % 8;
	if (currentColumn == 0) {
		if (callback != NULL) {
			callback->call();
		}
		currentPattern = nextPattern;
	}
}

} /* namespace us_cownet_lamps_simple */
