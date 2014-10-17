// Arduino timer CTC interrupt example
// www.engblaze.com

// avr-libc library includes
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

static const byte LEDPIN = 2;
static const unsigned int MAX_CYCLE = 15624;
static const unsigned int MIN_CYCLE = 156;

void setup()
{
    pinMode(LEDPIN, OUTPUT);

    // initialize Timer1
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR1A = MAX_CYCLE;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
    Serial.begin(28800);
}

static long count = 0;
static long startTime = 0;
void loop()
{
	count++;
	if (millis() - startTime > 1000) {
		Serial.println(count);
		count = 0;
		startTime = millis();
	}
    // do some crazy stuff while my LED keeps blinking
}

ISR(TIMER1_COMPA_vect)
{
	const int pinValue = digitalRead(LEDPIN);
    digitalWrite(LEDPIN, !pinValue);
    OCR1A = OCR1A * 4 / 5;
    if (OCR1A < MIN_CYCLE) {
    	OCR1A = MAX_CYCLE;
    }
}


