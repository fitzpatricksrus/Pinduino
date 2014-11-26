/*
 * SimpleMatrixPins.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#include "SimpleMatrixPins.h"

namespace pins {

SimpleMatrixPins::SimpleMatrixPins(OutputPins* colPinsIn, OutputPins* rowPinsIn)
: pattern(0), currentColumn(0), currentColumnPattern(0, 0), rowPins(rowPinsIn), colPins(colPinsIn)
{
}

SimpleMatrixPins::~SimpleMatrixPins() {
}

void SimpleMatrixPins::initPins() {
	currentColumn = 0;
	currentColumnPattern.setPinValues(pattern->getRowCount(), (*pattern)[currentColumn]);
	colPins->initPins();
	rowPins->initPins();
}

void SimpleMatrixPins::setPattern(MatrixPattern* patternIn) {
	pattern = patternIn;
}

void SimpleMatrixPins::latch() {
	// latch in the current row.
	rowPins->latch();
}

byte SimpleMatrixPins::getCurrentColumn() {
	return currentColumn;
}

void SimpleMatrixPins::setCurrentColumn(byte column) {
	currentColumn = column;
	currentColumnPattern.setPinValues(pattern->getRowCount(), (*pattern)[currentColumn]);
	rowPins->setPinPattern(&currentColumnPattern);
}

void SimpleMatrixPins::loop() {
	latch();
	currentColumn = (currentColumn + 1) % pattern->getColCount();
	setCurrentColumn(currentColumn);
}

} /* namespace pins */
