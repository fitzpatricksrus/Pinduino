/*
 * MaxSketch.ino
 *
 *  Created on: Oct 26, 2014
 *      Author: Dad
 */

#include <Arduino.h>
#include "Tests/Debug.h"

enum MAX7221_COMMAND {
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
} MAX7221_COMMAND;

void send7221Command(int command, int value)
{
   digitalWrite(SS,LOW); //chip select is active low
   //2-byte data transfer to the 7221
   SPI.transfer(command);
   SPI.transfer(value);
   digitalWrite(SS,HIGH); //release chip, signal end transfer
   Serial << _HEX(command) << " " << _BIN(value) << endl;
}

bool life[8][8];
bool plife[8][8];

static LedControl* control;

void MAXSetup() {
	Serial.begin(57200);
	Serial << ">setup" << endl;
	control = new LedControl(MOSI, SCK, SS);
	control->setIntensity(0, 0x01);
	control->shutdown(0, false);
	Serial << "<setup" << endl;
    randomSeed(analogRead(0));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			life[i][j] = random(2) != 0;
		}
	}
}

int p(int value) {
	if (value < 0) {
		return 7;
	} else if (value > 7) {
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
				cnt = cnt + (plife[p(x+dx)][p(y+dy)]) ? 1 : 0;
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
void MAXLoop() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			plife[i][j] = life[i][j];
			Serial << ((plife[i][j]) ? "*" : ".");
		}
		Serial << "    ";
		for (int j = 0; j < 8; j++) {
			int cnt = countAround(i, j);
			Serial << cnt;
		}
		Serial << endl;
	}
	Serial << endl;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int cnt = countAround(i, j);
			if (cnt < 2) {
				life[i][j] = false;
			} else if (cnt == 2) {
				// leave alone
			} else if (cnt == 3) {
				life[i][j] = true;
			} else {
				life[i][j] = false;
			}
		}
	}

	digitalWrite(SS, HIGH);
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			control->setLed(0, row, col, life[row][col]);
			Serial << ((life[row][col]) ? "*" : ".");
		}
		Serial << endl;
	}
	digitalWrite(SS, LOW);
	Serial << endl;
	delay(500);
}



