#include <Arduino.h>

//The setup function is called once at startup of the sketch

#if 0
enum {
	SW_COL_1 = 1,
	SW_ROW_2 = 2,
	SW_ROW_1 = 5,
	LMP_ROW = 7,
	LMP_COL = 8,
	SOL_2 = 9,
	SOL_4 = 10,
	SOL_3 = 11,
	SOL_1 = 12,
	TRIAC = 13,
	D7 = 15,
	D6 = 17,
	D5 = 19,
	D4 = 21,
	D3 = 23,
	D2 = 25,
	D1 = 27,
	D0 = 29,
	BLANK = 31,
	SW_JMP_1 = 32,
	SW_JPM_2 = 33,
	ZERO_CROSS = 34
} WPC_J111;	//22 pins used
#endif
enum WPC_J111 {
	SW_COL_1,
	SW_ROW_2,
	SW_ROW_1,
	LMP_ROW,
	LMP_COL,
	SOL_2,
	SOL_4,
	SOL_3,
	SOL_1,
	TRIAC,
	D7,
	D6,
	D5,
	D4,
	D3,
	D2,
	D1,
	D0,
	BLANK,		//blanking from driver baord
	SW_JMP_1,	//input jumper from driver board
	SW_JPM_2,	//input jumper from driver board
	ZERO_CROSS	//zero cross from driver board
};	//22 pins used

static const byte FIRST_INPUT_PIN = 2;
static const byte FIRST_OUTPUT_PIN = 24;


void setup()
{
	for (byte i = SW_COL_1; i < ZERO_CROSS; i++) {
		pinMode(FIRST_INPUT_PIN + i, INPUT);
		pinMode(FIRST_OUTPUT_PIN + i, OUTPUT);
	}
}

void loop()
{
	for (byte i = SW_COL_1; i < ZERO_CROSS; i++) {
		digitalWrite(FIRST_OUTPUT_PIN + i, digitalRead(FIRST_INPUT_PIN + i));
	}
}
