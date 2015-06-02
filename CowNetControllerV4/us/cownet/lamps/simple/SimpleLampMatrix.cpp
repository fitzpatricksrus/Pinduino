#include "SimpleLampMatrix.h"

#include "SimpleLampPattern.h"

namespace us_cownet_lamps_simple {
	
SimpleLampMatrix::SimpleLampMatrix(PinballOutputController* controllerIn, long nanosIn) 
: controller(controllerIn), micros(nanosIn), currentColumn(0), 
  currentPattern(&SimpleLampPattern::ALL_OFF), nextPattern(&SimpleLampPattern::ALL_OFF), 
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
		// start refresh
	} if (currentPattern != NULL && nextPattern == NULL) {
		// stop refresh
	}
}

void SimpleLampMatrix::setSyncCallback(Runnable* callback) {
	this->callback = callback;
}

void SimpleLampMatrix::tock() {
	controller->write(PinballOutputController::LAMP_COL, (byte)0);
	controller->write(PinballOutputController::LAMP_ROW, currentPattern->getPattern()[currentColumn]);
	controller->write(PinballOutputController::LAMP_COL, (byte)(1 << currentColumn));
	currentColumn = (currentColumn + 1) % 8;
	if (currentColumn == 0) {
		currentPattern = nextPattern;
		if (callback != NULL) {
			(*callback)();
		}
	}
}

} /* namespace us_cownet_lamps_simple */
