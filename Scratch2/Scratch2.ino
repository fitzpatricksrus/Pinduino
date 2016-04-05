#include <Arduino.h>
#include <debug.h>

typedef enum {
	NONE 	 = 0b00000000,
	FADE_ON  = 0b10000000,
	FADE_OFF = 0b01000000,
	BLINK    = 0b11000000,
	MODE_MASK   = 0b11000000,
	VALUE_MASK  = 0b00111111,
} LightingMode;

static const int PWM_BITS = 6;
static const int MAX_PWM_VALUE = 1 << PWM_BITS;
static const int MAX_FADE = MAX_PWM_VALUE;

class LampData {
public:
	bool exitFlag;
	bool ownedByPru;
	int offset;
	int size;
	byte *data;
};

static int pins[] = { 22, 26, 30, 34, 38, 42, 46, 50 };
static void writeColumn(bool* value, int column) {
	for (int i = 0; i < 8; i++) {
		digitalWrite(pins[i], column != i);
	}
	digitalWrite(A4, LOW);
	digitalWrite(A4, HIGH);

	for (int i = 0; i < 8; i++) {
		digitalWrite(pins[i], value[i] == false);
	}
	digitalWrite(A5, LOW);
	digitalWrite(A5, HIGH);
}

static void refreshOnePage(int fadeLevel, int pmwCycle, int size, byte* data) {
	bool columnBuffer[8];
	for (int i = 0; i < size; i++) {
		int bit = i % 8;
		int mode = data[i] & MODE_MASK;
		int value = data[i] & VALUE_MASK;
		switch (mode) {
		case FADE_OFF:
            if (fadeLevel == MAX_FADE-1) {
//                data[i] = 0;
            }
			columnBuffer[bit] = (value > (fadeLevel) + pmwCycle);
			break;
        case FADE_ON:
            if (fadeLevel == MAX_FADE-1) {
//                data[i] = value;
            }
			columnBuffer[bit] = (value > (MAX_FADE - fadeLevel) + pmwCycle);
			break;
        case BLINK: {
            if (fadeLevel < MAX_FADE / 2) {
    			columnBuffer[bit] = (value > (MAX_FADE - fadeLevel*2) + pmwCycle);
            } else {
            	int fadeLevel = fadeLevel - MAX_FADE / 2;
    			columnBuffer[bit] = (value > (fadeLevel*2) + pmwCycle);
            }
			break; }
        case NONE:
        default:
			fadeLevel = fadeLevel & VALUE_MASK;
			columnBuffer[bit] = (value > pmwCycle);
		}
		if (bit == 7) { //flush column
			writeColumn(columnBuffer, i / 8);
		}
	}
	if ((size % 8) != 0) { // partial column
		writeColumn(columnBuffer, size / 8);
	}
}

static LampData lampData;

static void refreshOnePWMCycle(int fadeLevel) {
	for (int pmwCycle = 0; pmwCycle < MAX_PWM_VALUE - 1; pmwCycle++) {
		refreshOnePage(fadeLevel, pmwCycle, lampData.size, &(lampData.data[lampData.offset]));
	}
}

void setup2() {
}

static byte rawData[] = {
	    0b00000000,
	    0b00001111 | FADE_OFF,
	    0b00011111 | FADE_OFF,
	    0b00111111 | FADE_OFF,
	    0b00111111 | FADE_ON,
	    0b00011111 | FADE_ON,
	    0b00001111 | FADE_ON,
	    0b00111111 | BLINK,
	    0b00000000,
	    0b00001111 | FADE_OFF,
	    0b00011111 | FADE_OFF,
	    0b00111111 | FADE_OFF,
	    0b00111111 | FADE_ON,
	    0b00011111 | FADE_ON,
	    0b00001111 | FADE_ON,
	    0b00111111 | BLINK,
	    0b00000000,
	    0b00001111 | FADE_OFF,
	    0b00011111 | FADE_OFF,
	    0b00111111 | FADE_OFF,
	    0b00111111 | FADE_ON,
	    0b00011111 | FADE_ON,
	    0b00001111 | FADE_ON,
	    0b00111111 | BLINK,
	    0b00000000,
	    0b00001111 | FADE_OFF,
	    0b00011111 | FADE_OFF,
	    0b00111111 | FADE_OFF,
	    0b00111111 | FADE_ON,
	    0b00011111 | FADE_ON,
	    0b00001111 | FADE_ON,
	    0b00111111 | BLINK,
};

static byte moreData[] = {
		0,1,2,3,4,5,6,7,8,9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31,32,33,34,35,36,37,38,39,
		40,41,42,43,44,45,46,47,48,49,
		50,51,52,53,54,55,56,57,58,59,
		60,61,62,63
};

void generate() {
	for (int ndx = 0; ndx < MAX_FADE; ndx++) {
		refreshOnePWMCycle(ndx);
	}
}

void loop2() {
	/*
	Serial.begin(57600);

	pinMode(A14, OUTPUT);
	digitalWrite(A14, false);
	pinMode(A15, OUTPUT);
	digitalWrite(A15, false);
	for (int i = 0; i < 8; i++) {
		pinMode(pins[i], OUTPUT);
		digitalWrite(pins[i], false);
	}

	lampData.exitFlag = false;
	lampData.ownedByPru = true;
	lampData.size = 32;
	lampData.offset = 0;
	lampData.data = &rawData[0];

	int ndx = 0;

	while (true) {
		lampData.data = &rawData[0];
		lampData.ownedByPru = true;
		refreshOnePWMCycle(ndx);
		ndx = (ndx + 1) % (MAX_FADE);
	}
	*/
}

