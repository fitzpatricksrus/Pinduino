#include <Arduino.h>

#include "LampMatrix7221.h"
#include "WPCLampMatrix.h"

#define _DEBUG_
#ifdef _DEBUG_
#include <debug.h>
#endif

static const byte COL_COUNT = 2; //24;
static const byte ROW_COUNT = 2;

static bool life[COL_COUNT][ROW_COUNT];
static bool plife[COL_COUNT][ROW_COUNT];
static bool p2life[COL_COUNT][ROW_COUNT];

static const byte firstDataPin = 4;
static const byte rowSelectPin = 3;
static const byte colSelectPin = 2;
static WPCLampMatrix xmitMatrix(colSelectPin, rowSelectPin, firstDataPin);

void MAXSetup() {
	xmitMatrix.init();
    randomSeed(analogRead(1));
	for (int col = 0; col < COL_COUNT; col++) {
		for (int row = 0; row < ROW_COUNT; row++) {
			life[col][row] = random(2) != 0;
		}
	}
}

int pCol(int value) {
	if (value < 0) {
		return COL_COUNT - 1;
	} else if (value >= COL_COUNT) {
		return 0;
	} else {
		return value;
	}
}

int pRow(int value) {
	if (value < 0) {
		return ROW_COUNT - 1;
	} else if (value >= ROW_COUNT) {
		return 0;
	} else {
		return value;
	}
}

int countAround(int x, int y) {
	int cnt = 0;
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx != 0 || dy != 0) {
				cnt = cnt + ((plife[pCol(x+dx)][pRow(y+dy)]) ? 1 : 0);
			}
		}
	}
	return cnt;
}

/*
Any live cell with fewer than two live neighbours dies, as if caused by under-population.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overcrowding.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 */

static int unchangedCount = 0;

void MAXLoop() {
	for (int col = 0; col < COL_COUNT; col++) {
		for (int row = 0; row < ROW_COUNT; row++) {
			p2life[col][row] = plife[col][row];
			plife[col][row] = life[col][row];
		}
	}

	for (int col = 0; col < COL_COUNT; col++) {
		for (int row = 0; row < ROW_COUNT; row++) {
			int cnt = countAround(col, row);
			if (cnt < 2) {
				life[col][row] = false;
			} else if (cnt == 2) {
				// leave alone
			} else if (cnt == 3) {
				life[col][row] = true;
			} else {
				life[col][row] = false;
			}
		}
	}

	unchangedCount++;
	for (int col = 0; col < COL_COUNT; col++) {
		byte colValue = 0;
		for (int row = 0; row < ROW_COUNT; row++) {
			if (life[col][row]) {
				colValue = colValue | (1 << row);
			}
/*			if (life[col][row] != plife[col][row]) {
				unchangedCount = 0;
			} */
			if ((life[col][row] != plife[col][row]) && (life[col][row] != p2life[col][row])) {
				unchangedCount = 0;
			}
		}
		xmitMatrix.setColumn(col, colValue);
//		Serial << col << "  " << _BIN(colValue) << endl;
	}
//	Serial << endl;
	if (unchangedCount > 6) {
		for (int col = 0; col < COL_COUNT; col++) {
			for (int row = 0; row < ROW_COUNT; row++) {
				life[col][row] = random(2) != 0;
			}
		}
	}
	delay(500);
}

static byte col = 0;
static byte row = 0;

void nextDot() {
	xmitMatrix.setColumn(col, 1 << row);
//	delayMicroseconds(2000000);
//	delayMicroseconds(125);
	delay(100);
	row++;
	if (row >= ROW_COUNT) {
		row = 0;
		xmitMatrix.setColumn(col, 0);
		col++;
		if (col >= COL_COUNT) {
			col = 0;
		}
	}
}

void nextDotA() {
	xmitMatrix.setRows(1 << row);
//	delayMicroseconds(2000000);

	delay(150);
	row++;
	if (row >= ROW_COUNT) {
		row = 0;
		col++;
		if (col >= COL_COUNT) {
			col = 0;
		}
		xmitMatrix.setRows(0);
		xmitMatrix.setColumn(col);
	}
}

void nextDot2() {
	xmitMatrix.setColumn(col, 1 << row);
	delay(80);

	col++;
	if (col >= COL_COUNT) {
		col = 0;
		xmitMatrix.setColumn(col, 0);
		row++;
		if (row >= ROW_COUNT) {
			row = 0;
		}
	}
}

void colTest() {
	xmitMatrix.setColumn(col);
	xmitMatrix.setRows(-1);
	delay(500);
	col++;
	if (col >= COL_COUNT) {
		col = 0;
	}
}

void col1Test() {
	xmitMatrix.setColumn(3, 1 << row);
	row++;
	if (row >= ROW_COUNT) {
		row = 0;
	}
}

void rowTest() {
	xmitMatrix.setColumn(0);
	xmitMatrix.setRows(1 << row);
	delay(500);
	row++;
	if (row >= ROW_COUNT) {
		row = 0;
	}
}

inline void togglePin2() {
	digitalWrite(2, LOW);
	digitalWrite(2, HIGH);
}


void justOneDot() {
	xmitMatrix.setColumn(0, 0);
	xmitMatrix.setColumn(1, 0);
}


void setup() {
#ifdef _DEBUG_
	Serial.begin(57600);
#endif
	MAXSetup();
}

void loop() {
//	justOneDot();
//	MAXLoop();
	nextDot();
//	while (1) togglePin2();
//	nextDotA();
//	nextDot2();
//	rowTest();
//	colTest();
//	col1Test();
//	attachInterrupt(2, handleFallingEdge, FALLING);
}
