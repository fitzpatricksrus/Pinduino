#include "SimpleLampMatrix.h"

#include "SimpleLampPattern.h"

#include "TimerUtil.h"

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

static SimpleLampMatrix* matrix = NULL;
static void isrCallback() {
	if (matrix) matrix->tock();
}

void SimpleLampMatrix::setPattern(LampPattern* lamps) {
	nextPattern = lamps;
	if (currentPattern == NULL && nextPattern != NULL) {
		TimerUtil::attachInterrupt(isrCallback, 2000);
	} if (currentPattern != NULL && nextPattern == NULL) {
		TimerUtil::detachInterrupt();
	}
}

void SimpleLampMatrix::setSyncCallback(void (*callback)()) {
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
