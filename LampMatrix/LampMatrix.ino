// #include "FlexiTimer2.h"

// #include "MatrixColumnPattern.h"
#include "OutputPins.h"
#include "MatrixPins.h"
#include "ConcreteMatrixPattern.h"
#include "Arduino.h"
#include "Logging.h"

static const Time TICKS_PER_COLUMN = 2000;

// static int ROW_PIN_NUMBERS[] = { 3, 5, 6, 9, 10, 11 };
static int ROW_PIN_NUMBERS[] = { 3, 4 };
static OutputPins ROW_PINS(2, ROW_PIN_NUMBERS);
// static int COL_PIN_NUMBERS[] = { 2, 8, 4, 7, 12 };
static int COL_PIN_NUMBERS[] = { 5, 6  };
static OutputPins COL_PINS(2, COL_PIN_NUMBERS);
static MatrixPins LAMP_MATRIX(COL_PINS, ROW_PINS, TICKS_PER_COLUMN);

static ConcreteMatrixPattern<2,2>::ValueArray MATRIX_VALUES1 = {
    { 1, 99 },
    { 1, 99 },
};
static ConcreteMatrixPattern<2,2> PATTERN1(MATRIX_VALUES1);

static ConcreteMatrixPattern<2,2>::ValueArray MATRIX_VALUES2 = {
    { 99, 5 },
    { 99, 5 }
};
static ConcreteMatrixPattern<2,2> PATTERN2(MATRIX_VALUES2);

long count = 0;
Time start;
long matrix = 0;


void setup() {
//    Logging::DEFAULT_LOG.init(Logging::LOG_LEVEL_ERROR, 115200);
    LAMP_MATRIX.initialize();
    LAMP_MATRIX.setPattern(&PATTERN1);
    Serial.begin(115200);
//	ROW_PINS.initializeDigitalPins(LOW);
//	COL_PINS.initializeDigitalPins(LOW);
    start = millis();
}


void loop() {
	count++;
	LAMP_MATRIX.refresh(micros());
    Time duration = millis() - start;
    if (duration > 2000) {
    	Serial.println(String("avg: ")+(count / 10));
    	count = 0;
    	matrix++;
    	if (matrix % 2 == 0) {
    		LAMP_MATRIX.setPattern(&PATTERN1);
    	} else {
    		LAMP_MATRIX.setPattern(&PATTERN2);
    	}
    	start = millis();
    }
}
