#include <SPI.h>
#include <ShiftBrite.h>

static ShiftBrite sb;
static const int MAX_VALUE = 512;
static int r = 0, rRate = 1;
static int g = MAX_VALUE / 3 * 2, gRate = 1;
static int b = MAX_VALUE / 3, bRate = 1;

static inline int cycleValue(int x) {
	int y = x % (MAX_VALUE * 2);
	if (y >= MAX_VALUE) {
		y = y - MAX_VALUE;
		return MAX_VALUE - y;
	} else {
		return y;
	}
}

static inline void latchWrite(byte pin, byte value) {
	digitalWrite(pin, (value == HIGH) ? HIGH : LOW);
	delayMicroseconds(100);
	digitalWrite(pin, (value == HIGH) ? LOW : HIGH);
}

//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(13, OUTPUT);
	sb.initPins();
    sb.setPower(100/2,140/2,120/2, ShiftBrite::C800MHz);
    sb.setColor(0,0,0);
    latchWrite(8, HIGH);
    digitalWrite(7, LOW);
}

// The loop function is called in an endless loop
void loop()
{
	r = (r + rRate) % (MAX_VALUE * 2);
	g = (g + gRate) % (MAX_VALUE * 2);
	b = (b + bRate) % (MAX_VALUE * 2);
	sb.setColor(cycleValue(r),
			cycleValue(g),
			cycleValue(b));
	sb.setColor(cycleValue(r + MAX_VALUE / 3 * 2),
			cycleValue(g + MAX_VALUE / 3 * 2),
			cycleValue(b + MAX_VALUE / 3 * 2));
	latchWrite(8, HIGH);
	delay(2);
}
