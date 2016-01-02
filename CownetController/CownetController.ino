#include "us/cownet/lamps/tests/PinballOutputControllerTest.h"
#include "us/cownet/lamps/tests/LampMatrixTest.h"
#include "us/cownet/lamps/tests/GreyscaleLampPatternTest.h"
#include "us/cownet/testing/Test.h"
#include "us/cownet/lamps/controllers/Max7221LampMatrix.h"
#include "us/cownet/lamps/controllers/DebugLampMatrix.h"
#include "us/cownet/timers/PeriodicEvent.h"

using namespace us_cownet_lamps_tests;
using namespace us_cownet_testing;
using namespace us_cownet_lamps_controllers;
using namespace us_cownet_timers;


//static LampMatrix* wpcLampMatrix = LampMatrixTest::createTestMatrix();
static Max7221LampMatrix max7221LampMatrix(10L*1000L, 10);
//static Max7221LampMatrix max7221LampMatrix(0, 9);
//static DebugLampMatrix debugMatrix(1);

LampMatrix* matrix = &max7221LampMatrix;

//static PinballOutputControllerTest pinballOutputControllerTest(PinballOutputControllerTest::createTestController());
//static LampMatrixTest lampMatrixTest(matrix);
static GreyscaleLampPatternTest greyPatternTest(matrix);

//static Test& test = pinballOutputControllerTest;
//static Test& test = lampMatrixTest;
static Test& test = greyPatternTest;

static PeriodicEvent event;

void setup()
{
	Serial.println("SETUP");
	Serial.begin(57600);
	pinMode(51, OUTPUT);
	pinMode(52, OUTPUT);
	pinMode(53, OUTPUT);
	pinMode(9, OUTPUT);
	test.setup();
	event = PeriodicEvent::forTime(1000L * 1000L);
}

static int cnt = 0;

void loop()
{
	test.loop();
	if (event.isTime()) {
		Serial.println(cnt);
		cnt = 0;
	} else {
		cnt++;
	}

}
