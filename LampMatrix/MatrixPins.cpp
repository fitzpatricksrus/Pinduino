/*
 * MatrixPins.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: Dad
 */

#include "MatrixPins.h"
#include "Arduino.h"

MatrixPins::MatrixPins(const OutputPins& colsIn, const OutputPins& rowsIn, Time timePerColumnIn)
: refreshRate(timePerColumnIn*colsIn.getPinCount()), timePerColumn(timePerColumnIn), columns(colsIn), rows(rowsIn), currentPattern(0)
{
/*    pwmCutoffs = new Time[PWM_STEPS];
	for (int i = 0; i < PWM_STEPS; i++) {
		pwmCutoffs[i] = map(i, 0, PWM_STEPS-1, 0, timePerColumn);
	}
	colStarts = new Time[columns.getPinCount()];
	colStops = new Time[columns.getPinCount()];
	colStarts[0] = 0;
	colStops[0] = timePerColumn;
	for (int i = 1; i < columns.getPinCount(); i++) {
		colStarts[i] = colStops[i-1];
		colStops[i] = colStarts[i] + timePerColumn;
	} */
}

MatrixPins::~MatrixPins() {
//	delete [] colStarts;
//	delete [] colStops;
}

void MatrixPins::initialize(int pulseWaveSteps) {
	columns.initializeDigitalPins(LOW);
	rows.initializeDigitalPins(LOW);
    pwmCutoffs = new Time[pulseWaveSteps];
	for (int i = 0; i < pulseWaveSteps; i++) {
		pwmCutoffs[i] = map(i, 0, pulseWaveSteps-1, 0, timePerColumn);
	}
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

/*	Time timeIntoThisCycle = now  % refreshRate;	// time since we started this matrix refresh
	Time timeIntoThisColumn = timeIntoThisCycle % timePerColumn;

	for (int columnNdx = 0; columnNdx < columns.getPinCount(); columnNdx++) {
		if ((timeIntoThisCycle >= colStarts[columnNdx]) && (timeIntoThisCycle < colStops[columnNdx])) {
			columns.setDigitalPin(columnNdx, HIGH);
			for (int i = 0; i < rows.getPinCount(); i++) {
				int rowValue = (*currentPattern)[columnNdx][i];
				if (timeIntoThisColumn < pwmCutoffs[rowValue]) {
					rows.setDigitalPin(i, HIGH);
				} else {
					rows.setDigitalPin(i, LOW);
				}
			}
		} else {
			// we've passed this column so turn it off
			columns.setDigitalPin(columnNdx, LOW);
		}
	} */
}

void MatrixPins::setPattern(MatrixPattern* pattern) {
	currentPattern = pattern;
}
