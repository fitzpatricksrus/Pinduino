#include <Arduino.h>
//
//  main.cpp
//  Dumb
//
//  Created by Dad on 9/13/14.
//  Copyright (c) 2014 Dad. All rights reserved.
//

// #include <iostream>
// #include "Header.h"
/*
typedef int Matrix[5][6];

//-------------------------------------------------
// Simple class to keep track of the state of the
// output pins in order to minimize flicker with
// PWM output and to abstract away the need to have
// pin number constants all over the place.

class OutputPins {
public:
    OutputPins(int pins[], int pinCount);
    void initialize();
    int getPin(int pinNdx);
    void setPin(int pinNdx, int value);
    int getPinCount();
private:
    int* pinNumber;
    int* pinValue;
    int pinCount;
};

OutputPins::OutputPins(int pinsIn[], int pinCountIn)
: pinNumber(&pinsIn[0]), pinValue(0), pinCount(pinCountIn)
{
}

void OutputPins::initialize() {
    // this setup could easily be in the constructor if
    // we allocated the OutputPins in the setup() method,
    // but since we do it statically we need to wait
    // until setup() is called to initialize output pins.
    pinValue = new int[pinCount];
    for (int i = 0; i < pinCount; i++) {
        pinMode(pinNumber[i], OUTPUT);
        digitalWrite(pinNumber[i], LOW);
        pinValue[i] = LOW;
    }
}

int OutputPins::getPin(int pinNdx) {
    return pinValue[pinNdx];
}

void OutputPins::setPin(int pinNdx, int value) {
    if (value == getPin(pinNdx)) return;
    //  Serial.println(String("Pin Changed: ")+pinNumber[pinNdx]+" = "+value+" from "+getPin(pinNdx));
    if (value == LOW || value == HIGH) {
        digitalWrite(pinNumber[pinNdx], value);
    } else {
        analogWrite(pinNumber[pinNdx], value);
    }
    pinValue[pinNdx] = value;
}

int OutputPins::getPinCount() {
    return pinCount;
}

//-------------------------------------------------
class Effect {
public:
	virtual ~Effect() {}
    virtual int effect(int value) = 0;
};

class NullEffect : public Effect {
public:
    virtual int effect(int value);
};

int NullEffect::effect(int value) {
    return value;
}

static NullEffect NullEffect_INSTANCE = NullEffect();

class FadeInOutEffect : public Effect {
public:
    FadeInOutEffect(int fadeRate);
    FadeInOutEffect(const FadeInOutEffect& other);
    virtual int effect(int value);
private:
    int fadeRate;
};

FadeInOutEffect::FadeInOutEffect(int fadeRateIn)
: fadeRate(fadeRateIn)
{
}

FadeInOutEffect::FadeInOutEffect(const FadeInOutEffect& other)
: fadeRate(other.fadeRate)
{
}

int FadeInOutEffect::effect(int value) {
    unsigned long now = millis();
    unsigned long bla = now % (fadeRate * 2);
    if (bla >= fadeRate) {
        bla -= fadeRate;
        value = value - (value * bla / fadeRate);
    } else {
        value = value * bla / fadeRate;
    }
    return (value != 1) ? value : 0;
}

static FadeInOutEffect* FadeInOutEffect_INSTANCE = new FadeInOutEffect(1024);

//-------------------------------------------------
// LampConfiguration keeps track of all the lights in the matrix
// and of what brightness they should be set to.
class LampConfiguration {
public:
    LampConfiguration(Matrix& matrix);
    LampConfiguration(Matrix& matrix, Effect& effect);
    void reset();
    void refresh(OutputPins& rows, OutputPins& columnPins);
private:
    static const int REFRESH_DELAY = 3; //ms
    Matrix& matrix;
    unsigned long lastRefreshTime;
    int lastRefreshColumn;
    Effect& effect;
};

LampConfiguration::LampConfiguration(Matrix& matrixIn)
: matrix(matrixIn), lastRefreshTime(0), lastRefreshColumn(0), effect(NullEffect_INSTANCE)
{
}

LampConfiguration::LampConfiguration(Matrix& matrixIn, Effect& effectIn)
: matrix(matrixIn), lastRefreshTime(0), lastRefreshColumn(0), effect(effectIn)
{
}

void LampConfiguration::reset() {
    lastRefreshTime = 0;
}

void LampConfiguration::refresh(OutputPins& rowPins, OutputPins& columnPins) {
    unsigned long now = millis();
    if (now - lastRefreshTime >= REFRESH_DELAY) {
        //turn off current column
        columnPins.setPin(lastRefreshColumn, LOW);
        //calculate next column
        lastRefreshColumn = (lastRefreshColumn + 1) % columnPins.getPinCount();
        //update all the rows
        for (int i = 0; i < rowPins.getPinCount(); i++) {
            rowPins.setPin(i, effect.effect(matrix[lastRefreshColumn][i]));
        }
        //turn on new column
        columnPins.setPin(lastRefreshColumn, HIGH);
        lastRefreshTime = now;
    }
}

//-------------------------------------------------
class LightShow {
public:
    LightShow(int size);
    LightShow addPlan(LampConfiguration& plan, unsigned long duration);
private:

};

//-------------------------------------------------
// The actual output pins we will use
static int ROW_PIN_NUMBERS[] { 3, 5, 6, 9, 10, 11  };
static int COL_PIN_NUMBERS[] { 2, 8, 4, 7, 12 };
OutputPins ROW_PINS(ROW_PIN_NUMBERS, 6);
OutputPins COL_PINS(COL_PIN_NUMBERS, 5);

static int PLAN1[][6] = {
    { 255, 255, 255, 255, 255, 255 },
    { 255, 255, 255, 255, 255, 255 },
    { 255, 255,  32,  32, 255, 255 },
    { 255, 255, 255, 255, 255, 255 },
    { 255, 255, 255, 255, 255, 255 }
};

static int PLAN2[][6] = {
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
};




LampConfiguration config1(PLAN1, FadeInOutEffect_INSTANCE);



//-------------------------------------------------

void setup() {
    COL_PINS.initialize();
    ROW_PINS.initialize();
    Serial.begin(115200);
}

void loop() {
    //    unsigned long now = millis();
    config1.refresh(ROW_PINS, COL_PINS);
}

*/

void setup() {
}

void loop() {
}
