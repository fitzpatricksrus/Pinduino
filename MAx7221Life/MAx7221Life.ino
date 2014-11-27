#include <Arduino.h>

#include "Tests/Debug.h"
#include "SPI.h"

class MAX7221_COMMAND {
public:
	enum {
		noop =      B00000000,
		digit0 =    B00000001,
		digit1 =    B00000010,
		digit2 =    B00000011,
		digit3 =    B00000100,
		digit4 =    B00000101,
		digit5 =    B00000110,
		digit6 =    B00000111,
		digit7 =    B00001000,
		decode =    B00001001,
		intensity = B00001010,
		scanLimit = B00001011,
		enable =    B00001100,
		unused1 =   B00001101,
		unused2 =   B00001110,
		test =      B00001111
	};
};


static const byte COL_COUNT = 24;
static const byte ROW_COUNT = 8;

bool life[COL_COUNT][ROW_COUNT];
bool plife[COL_COUNT][ROW_COUNT];

static byte SLAVE_PIN[3] = {10, 9, 8};

void send7221Command(byte device, byte command, int value)
{
   digitalWrite(SLAVE_PIN[device],LOW); //chip select is active low
   //2-byte data transfer to the 7221
   SPI.transfer(command);
   SPI.transfer(value);
   digitalWrite(SLAVE_PIN[device],HIGH); //release chip, signal end transfer
}

void MAXSetup() {
	SPI.begin();
	for (int i = 0; i <= (COL_COUNT / 3); i++) {
		pinMode(SLAVE_PIN[i], OUTPUT);
		send7221Command(i, MAX7221_COMMAND::test, false);
		send7221Command(i, MAX7221_COMMAND::intensity, 0x01);
		send7221Command(i, MAX7221_COMMAND::decode, false);
		send7221Command(i, MAX7221_COMMAND::scanLimit, 7);
		send7221Command(i, MAX7221_COMMAND::enable, true);
	}
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
			if (life[col][row] != plife[col][row]) {
				unchangedCount = 0;
			}
		}
		send7221Command(col / 8, MAX7221_COMMAND::digit0+(col % 8), colValue);
	}
	if (unchangedCount > 6) {
		for (int col = 0; col < COL_COUNT; col++) {
			for (int row = 0; row < ROW_COUNT; row++) {
				life[col][row] = random(2) != 0;
			}
		}
	}
	delay(150);
}

void setup() {
	MAXSetup();
}

void loop() {
	MAXLoop();
}
