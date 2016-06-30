#include <Arduino.h>
#include <debug.h>

static int ADDRESS_BITS = 2;
static int DATA_BITS = 2;
static int MAX_DATA_VALUE = (1 << DATA_BITS);
enum {
	WE_ = A0,
	OE_,
	CE_,
	ADDR0 = A3,
	ADDR1,
	ADDR2,
	ADDR3,
	ADDR4,
	DATA0 = A8,
	DATA1,
	DATA2,
	DATA3,
	DATA4,
	DATA5,
	DATA6,
	DATA7,
	END_PINS
};

static void writeAddress(int address) {
	for (int i = 0; i < ADDRESS_BITS; i++) {
		digitalWrite(ADDR0+i, (address & 0x01) ? HIGH : LOW);
		address = address >> 1;
	}
}

static void writeBits(int address, int value) {
	digitalWrite(WE_, HIGH);
	digitalWrite(OE_, HIGH);

	for (int i = 0; i < DATA_BITS; i++) {
		int pin = DATA0 + i;
		pinMode(pin, OUTPUT);
		digitalWrite(pin, (value & 0x01) ? HIGH : LOW);
		value = value >> 1;
	}

//	writeAddress(address);
	for (int i = 0; i < ADDRESS_BITS; i++) {
		digitalWrite(ADDR0+i, (address & 0x01) ? HIGH : LOW);
		address = address >> 1;
	}

	digitalWrite(WE_, LOW);
	digitalWrite(OE_, HIGH);

	delay(10);

	digitalWrite(OE_, HIGH);
	digitalWrite(WE_, HIGH);

	for (int i = 0; i < 8; i++) {
		pinMode(DATA0 + i, INPUT);
	}

}

static int readBits(int address) {
	digitalWrite(WE_, HIGH);
	digitalWrite(OE_, HIGH);

	//	writeAddress(address);
	for (int i = 0; i < ADDRESS_BITS; i++) {
		digitalWrite(ADDR0+i, (address & 0x01) ? HIGH : LOW);
		address = address >> 1;
	}

	for (int i = 0; i < 8; i++) {
		pinMode(DATA0 + i, INPUT);
	}

	digitalWrite(WE_, HIGH);
	digitalWrite(OE_, LOW);

	delay(10);

	int mask = 0x01;
	int value = 0;
	for (int i = 0; i < DATA_BITS; i++) {
		int pin = DATA0 + i;
		if (digitalRead(pin)) {
			value = value || mask;
		}
		mask = mask << 1;
	}

	digitalWrite(OE_, HIGH);
	digitalWrite(WE_, HIGH);

	return value;
}

static void writeMemory(int values[]) {
	for (int i = 0; i < MAX_DATA_VALUE; i++) {
		Serial << "writeBits(" << i << ", " << values[i] << ")" << endl;
		writeBits(i, values[i]);
	}
}

static void readMemory(int* values) {
	for (int i = 0; i < MAX_DATA_VALUE; i++) {
		values[i] = readBits(i);
		Serial << "readBits(" << i << ") = " << values[i] << endl;
	}
}

//The setup function is called once at startup of the sketch
void setup()
{
	for (int i = WE_; i < END_PINS; i++) {
		pinMode(WE_+i, INPUT);
	}

	digitalWrite(WE_, HIGH);
	digitalWrite(OE_, HIGH);
	digitalWrite(CE_, HIGH);
	pinMode(WE_, OUTPUT);
	pinMode(OE_, OUTPUT);
	pinMode(CE_, OUTPUT);

	// so they're low if they're ever output
	for (int i = ADDR0; i <= ADDR4; i++) {
		digitalWrite(i, LOW);
		pinMode(i, OUTPUT);
	}

	for (int i = DATA0; i <= DATA7; i++) {
		digitalWrite(i, LOW);
	}

	Serial.begin(57600);
}


void loop()
{
	Serial.println();
	Serial.println("-------------------------------------");
	Serial << "MAX_DATA_VALUE = " << MAX_DATA_VALUE << endl;
	digitalWrite(WE_, HIGH);
	digitalWrite(OE_, HIGH);
	digitalWrite(CE_, LOW);

	int dataOut[] = {3, 2, 1, 0};
	int dataIn[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dataOut[j] = (i + j) % 4;
		}
		writeMemory(dataOut);
		readMemory(dataIn);
	}

	digitalWrite(WE_, HIGH);
	digitalWrite(OE_, HIGH);
	digitalWrite(CE_, HIGH);
	delay(500);
}
