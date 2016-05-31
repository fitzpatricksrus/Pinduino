#include <Arduino.h>

static const int PWM_BITS = 4;
static const int MAX_PWM_VALUE = 1 << PWM_BITS;
static int COLUMN_SIZE = 14;

class LampData {
public:
	int size;
	byte *data;
};

static int pins[] = { 22,23,24,25, 26,27,28,29, 34,35,36,37, 38,39,40,41 };
static enum {
    DATA0,
    DATA1,
    DATA2,
    DATA3,
    DATA4,
    DATA5,
    DATA6,
    DATA7,
    DATA8,      //A0
    DATA9,      //A1
    DATA10,     //A2
    DATA11,     //A3
    DATA12,     //A4
    DATA13,     //A5
} SIGNAL;

inline void pinLow(int pin) {
    digitalWrite(pin, LOW);
}

inline void pinHigh(int pin) {
    digitalWrite(pin, HIGH);
}

inline void pinOn(int pin) {
    pinHigh(pin);
}

inline void pinOff(int pin) {
    pinLow(pin);
}

inline void on(int pin) {
    pinOn(pins[pin]);
}

inline void off(int pin) {
    pinOff(pins[pin]);
}

inline void signal(int ndx) {
    pinOn(pins[ndx]);
//    pinOn(pins[ndx]);
    pinOff(pins[ndx]);
//    pinOff(pins[ndx]);
}

static void writeColumn(bool* value, int column) {
    // update rows
	for (int i = 0; i < COLUMN_SIZE; i++) {
	    if (value[i]) {
	        on(i);
	    } else {
	        off(i);
	    }
	}
}

static void refreshOnePage(int pmwCycle, int size, byte* data) {
	bool columnBuffer[COLUMN_SIZE];
	for (int i = 0; i < size; i++) {
		int bit = i % 8;
		columnBuffer[bit] = (data[i] > pmwCycle);
		if (bit == COLUMN_SIZE - 1) { //flush column
			writeColumn(columnBuffer, i / COLUMN_SIZE);
		}
	}
	if ((size % COLUMN_SIZE) != 0) { // partial column
		writeColumn(columnBuffer, size / COLUMN_SIZE);
	}
}

static LampData lampData;

static void refreshOnePWMCycle() {
	for (int pmwCycle = 0; pmwCycle < MAX_PWM_VALUE - 1; pmwCycle++) {
		refreshOnePage(pmwCycle, lampData.size, lampData.data);
	}
}

static byte rawData[] = {
    0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0F,
	0x0F
};

void setupX() {
	for (int i = 0; i < 16; i++) {
		pinMode(pins[i], OUTPUT);
		on(i);
	}

	lampData.size = 15;
	lampData.data = &rawData[0];
}

void loopX() {
//    while (true) {
    	refreshOnePWMCycle();
//    }
}

