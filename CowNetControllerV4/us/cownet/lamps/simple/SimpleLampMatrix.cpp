#include "SimpleLampMatrix.h"

#include "SimpleLampPattern.h"

#include "TimerUtil.h"

namespace us_cownet_lamps_simple {

static SimpleLampMatrix* matrix = NULL;
void SimpleLampMatrix_Callback() {
	if (matrix) matrix->tock();
}

SimpleLampMatrix::SimpleLampMatrix(PinballOutputController* controllerIn, long nanosIn) 
: timer(&TimerUtil::DEFAULT_TIMER), controller(controllerIn), micros(nanosIn), currentColumn(0),
  currentPattern(&SimpleLampPattern::ALL_OFF), nextPattern(&SimpleLampPattern::ALL_OFF), 
  callback(0) {
}

SimpleLampMatrix::SimpleLampMatrix(TimerUtil* timerIn, PinballOutputController* controllerIn, long nanosIn)
: timer(timerIn), controller(controllerIn), micros(nanosIn), currentColumn(0),
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
		timer->attachInterrupt(&SimpleLampMatrix_Callback, 2000);
	} if (currentPattern != NULL && nextPattern == NULL) {
		timer->detachInterrupt();
	}
}

void SimpleLampMatrix::setSyncCallback(Callback* callbackIn) {
	callback = callbackIn;
	matrix = this;
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
