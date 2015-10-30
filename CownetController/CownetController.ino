#include "us/cownet/lamps/tests/PinballOutputControllerTest.h"
#include "us/cownet/lamps/tests/LampMatrixTest.h"
#include "us/cownet/testing/Test.h"
#include "us/cownet/lamps/controllers/Max7221LampMatrix.h"

using namespace us_cownet_lamps_tests;
using namespace us_cownet_testing;
using namespace us_cownet_lamps_controllers;


static LampMatrix* wpcLampMatrix = LampMatrixTest::createTestMatrix();
static Max7221LampMatrix max7221LampMatrix(10L*1000L, 10);

static PinballOutputControllerTest pinballOutputControllerTest(PinballOutputControllerTest::createTestController());
static LampMatrixTest lampMatrixTest(&max7221LampMatrix);

static Test& test = lampMatrixTest;

void setup()
{
	Serial.begin(57600);
	test.setup();
}

void loop()
{
	test.loop();
}
