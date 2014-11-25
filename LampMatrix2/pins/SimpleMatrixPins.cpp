/*
 * SimpleMatrixPins.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#include "SimpleMatrixPins.h"

namespace pins {

SimpleMatrixPins::SimpleMatrixPins(OutputPins* pinsIn)
: pattern(0), currentColumn(0), currentColumnPattern(0, 0), pins(pinsIn)
{
}

SimpleMatrixPins::~SimpleMatrixPins() {
}

void SimpleMatrixPins::initPins() {
	currentColumn = 0;
	currentColumnPattern.setPinValues(pattern->getRowCount(), (*pattern)[currentColumn]);
	for (byte i = 0; i < pattern->getColCount(); i++) {
		pins[i].initPins();
	}
}

void SimpleMatrixPins::setPattern(MatrixPattern* patternIn) {
	pattern = patternIn;
}

void SimpleMatrixPins::latch() {
	// latch in the current row.
	currentColumnPattern.setPinValues(pattern->getRowCount(), (*pattern)[currentColumn]);
	pins[currentColumn].setPinPattern(&currentColumnPattern);
	pins[currentColumn].latch();
}

byte SimpleMatrixPins::getCurrentColumn() {
	return currentColumn;
}

void SimpleMatrixPins::setCurrentColumn(byte column) {
	currentColumn = column;
}

void SimpleMatrixPins::loop() {
	latch();
	currentColumn = (currentColumn + 1) % pattern->getColCount();
}

} /* namespace pins */
