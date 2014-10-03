/*
 * MatrixPins.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: Dad
 */

#include "MatrixPins.h"
#include "Arduino.h"

MatrixPins::MatrixPins(const OutputPins& colsIn, const OutputPins& rowsIn, Time timePerColumnIn)
: refreshRate(timePerColumnIn*colsIn.getPinCount()), timePerColumn(timePerColumnIn),
  columns(colsIn), rows(rowsIn), currentPattern(0), pwmCutoffs(0)
{
}

MatrixPins::~MatrixPins() {
}

void MatrixPins::initialize(int pulseWaveSteps) {
	columns.initializeDigitalPins(LOW);
	rows.initializeDigitalPins(LOW);
}

void MatrixPins::refresh(Time now) {
    Time timeIntoThisCycle = now  % refreshRate;					// 0 - (refreshRate-1)
    int columnNdx = timeIntoThisCycle / timePerColumn;				// 0 - (columns - 1)
    Time timeIntoThisColumn = timeIntoThisCycle % timePerColumn;	// 0 - (timePerColumn -1)
    
    for (int col = 0; col < columns.getPinCount(); col++) {
        columns.setDigitalPin(col, (col == columnNdx) ? HIGH : LOW);
    }
    for (int i = 0; i < rows.getPinCount(); i++) {
        int rowValue = (*currentPattern)[columnNdx][i];
        if (timeIntoThisColumn < pwmCutoffs[rowValue]) {
            rows.setDigitalPin(i, HIGH);
        } else {
            rows.setDigitalPin(i, LOW);
        }
    }
}

void MatrixPins::setPattern(MatrixPattern* pattern) {
	if (pwmCutoffs != 0) delete[] pwmCutoffs;
	currentPattern = pattern;
	int pulseWaveSteps = pattern->getPWMSteps();
    pwmCutoffs = new Time[pulseWaveSteps];
	for (int i = 0; i < pulseWaveSteps; i++) {
		pwmCutoffs[i] = map(i, 0, pulseWaveSteps-1, 0, timePerColumn);
	}
}
