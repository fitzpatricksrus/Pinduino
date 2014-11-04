/*
 * MatrixPins.h
 *
 *  Created on: Sep 26, 2014
 *      Author: Dad
 */

#ifndef MATRIXPINS_H_
#define MATRIXPINS_H_

#include "MatrixPattern.h"
#include "../pins/DirectOutputPins.h"
#include "Arduino.h"

typedef unsigned long Time;

class MatrixPins {
  public:
  	MatrixPins(OutputPins* cols, OutputPins* rows, Time ticksPerColumn);
	MatrixPins(const MatrixPins& source);
	~MatrixPins();
	MatrixPins& operator=(const MatrixPins& other);
	void initialize();
	void refresh(Time nowMs);
	void setPattern(MatrixPattern* pattern);
	void setTicksPerColumn(Time ticksPerColumn);
  private:
	void recalcPWM(int steps);

	Time refreshRate;
	Time* pwmCutoffs;
    Time timePerColumn;
	OutputPins* columns;
	OutputPins* rows;
	MatrixPattern* currentPattern;
};


#endif /* MATRIXPINS_H_ */
