// #include "FlexiTimer2.h"

// #include "MatrixColumnPattern.h"
#include "OutputPins.h"
#include "MatrixPins.h"
#include "Arduino.h"
#include "Logging.h"
#include "Matrix8x8.h"

static const Time TICKS_PER_COLUMN = 2000;

static uint8_t ROW_PIN_NUMBERS[] = { 46,48,47,49,50,51,52,53,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45 };
static OutputPins ROW_PINS(24, ROW_PIN_NUMBERS);
static uint8_t COL_PIN_NUMBERS[] = { 2,3,4,5,6,7,8,9 };
static OutputPins COL_PINS(8, COL_PIN_NUMBERS);
static MatrixPins LAMP_MATRIX(COL_PINS, ROW_PINS, TICKS_PER_COLUMN);

long count = 0;
Time start;
long matrix = 0;

void setup() {
//    Logging::DEFAULT_LOG.init(Logging::LOG_LEVEL_ERROR, 115200);
    LAMP_MATRIX.initialize();
    LAMP_MATRIX.setPattern(Matrix8by8::getPattern(0));
    Serial.begin(115200);
    start = millis();
}

void loop() {
	count++;
	LAMP_MATRIX.refresh(micros());
    Time duration = millis() - start;
    if (duration > 1000) {
    	matrix++;
    	String msg("rate: ");
    	int pattern = matrix % 4;
    	msg = msg + count + " matrix: " + pattern;
		LAMP_MATRIX.setPattern(Matrix8by8::getPattern(pattern));
    	Serial.println(msg);
    	count = 0;
    	start = millis();
    }
}
