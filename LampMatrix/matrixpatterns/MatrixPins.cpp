/*
 * MatrixPins.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: Dad
 */

#include "MatrixPins.h"
#include "Arduino.h"

namespace matrixpatterns {

MatrixPins::MatrixPins(OutputPins* colsIn, OutputPins* rowsIn, Time timePerColumnIn)
: refreshRate(timePerColumnIn*colsIn->getPinCount()), pwmCutoffs(0), timePerColumn(timePerColumnIn),
  columns(colsIn), rows(rowsIn), currentPattern(0)
{
}

MatrixPins::~MatrixPins() {
}

void MatrixPins::initialize() {
	columns->setAllPins(LOW);
	rows->setAllPins(LOW);
}

void MatrixPins::refresh(Time now) {
    Time timeIntoThisCycle = now  % refreshRate;					// 0 - (refreshRate-1)
    uint8_t columnNdx = timeIntoThisCycle / timePerColumn;			// 0 - (columns - 1)
    Time timeIntoThisColumn = timeIntoThisCycle % timePerColumn;	// 0 - (timePerColumn -1)
    
    for (int col = columns->getPinCount() - 1; col >= 0; col--) {
       columns->setPin(col, col == columnNdx);
    }
    columns->latch();

    for (int i = rows->getPinCount() - 1; i >= 0 ; i--) {
    	uint8_t rowValue = (*currentPattern)[columnNdx][i];
    	rows->setPin(i, timeIntoThisColumn < pwmCutoffs[rowValue]);
    }
    rows->latch();
}

void MatrixPins::setPattern(MatrixPattern* pattern) {
	if (currentPattern == pattern) return;
	if (currentPattern == 0 || currentPattern->getPWMSteps() != pattern->getPWMSteps()) {
		recalcPWM(pattern->getPWMSteps());
	}
	currentPattern = pattern;
}

void MatrixPins::setTicksPerColumn(Time ticksPerColumn) {
	if (timePerColumn == ticksPerColumn) return;
	timePerColumn = ticksPerColumn;
	recalcPWM(currentPattern->getPWMSteps());
}

void MatrixPins::recalcPWM(int pulseWaveSteps) {
	if (pwmCutoffs != 0) delete[] pwmCutoffs;
	pwmCutoffs = new Time[pulseWaveSteps];
	for (int i = 0; i < pulseWaveSteps; i++) {
		pwmCutoffs[i] = map(i, 0, pulseWaveSteps-1, 0, timePerColumn);
	}
}

} // namespace matrixpatterns
