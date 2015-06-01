#include "SimpleLampMatrix.h"

#include "SimpleLampPattern.h"

namespace us_cownet_lamps_simple {
	
SimpleLampMatrix::SimpleLampMatrix(PinballOutputController* controllerIn, long nanosIn) 
: controller(controllerIn), nanos(nanosIn), currentColumn(0), 
  currentPattern(&SimpleLampPattern::ALL_OFF), nextPattern(&SimpleLampPattern::ALL_OFF), 
  callback(nullptr) {
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
	if (currentPattern == nullptr && nextPattern != nullptr) {
		// start refresh
	} if (currentPattern != nullptr && nextPattern == nullptr) {
		// stop refresh
	}
}

void SimpleLampMatrix::setSyncCallback(Runnable* callback) {
	this->callback = callback;
}

void SimpleLampMatrix::tock() {
	controller.write(PinballOutputController::Register.LAMP_COL, (byte)0);
	controller.write(PinballOutputController::Register.LAMP_ROW, currentLampPattern->getPattern()[currentColumn]);
	controller.write(PinballOutputController::Register.LAMP_COL, (byte)(1 << currentColumn));
	currentColumn = (currentColumn + 1) % 8;
	if (currentColumn == 0) {
		currentLampPattern = nextLampPattern;
		if (callback != nullptr) {
			callback.call();
		}
	}
}

} /* namespace us_cownet_lamps_simple */
