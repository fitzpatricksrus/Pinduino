/*
 * SimpleMatrixPins.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#include "SimpleMatrixPins.h"

namespace pins {

SimpleMatrixPins::SimpleMatrixPins(OutputPins* colPinsIn, OutputPins* rowPinsIn)
: pattern(0), currentColumnPattern(0, 0), columnSelectorPattern(0), rowPins(rowPinsIn), colPins(colPinsIn)
{
}

SimpleMatrixPins::~SimpleMatrixPins() {
}

void SimpleMatrixPins::initPins() {
	colPins->initPins();
	rowPins->initPins();
	rowPins->setPinPattern(&currentColumnPattern);
	colPins->setPinPattern(&columnSelectorPattern);
}

void SimpleMatrixPins::setPattern(MatrixPattern* patternIn) {
	pattern = patternIn;
	columnSelectorPattern.setColumnCount(pattern->getColCount());
	setCurrentColumn(0);
}

void SimpleMatrixPins::latch() {
	// latch in the current row.
	colPins->latch();
	rowPins->latch();
}

byte SimpleMatrixPins::getCurrentColumn() {
	return columnSelectorPattern;
}

void SimpleMatrixPins::setCurrentColumn(byte column) {
	columnSelectorPattern.setCurrentColumn(column);
	currentColumnPattern.setPinValues(pattern->getRowCount(), (*pattern)[columnSelectorPattern]);
	rowPins->setPinPattern(&currentColumnPattern);
}

void SimpleMatrixPins::loop() {
	latch();
	setCurrentColumn(++columnSelectorPattern);
}

} /* namespace pins */
