// Arduino timer CTC interrupt example
// www.engblaze.com

// avr-libc library includes
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define LEDPIN 2

void setup()
{
    pinMode(LEDPIN, OUTPUT);

    // initialize Timer1
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR1A = 15624;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
}

void loop()
{
    // do some crazy stuff while my LED keeps blinking
}

ISR(TIMER1_COMPA_vect)
{
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}

