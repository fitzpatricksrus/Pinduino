#include "us/cownet/lamps/tests/PinballOutputControllerTest.h"
#include "us/cownet/lamps/tests/LampMatrixTest.h"
#include "us/cownet/testing/Test.h"

using namespace us_cownet_lamps_tests;
using namespace us_cownet_testing;


static LampMatrix* lampMatrix = LampMatrixTest::createTestMatrix();

static PinballOutputControllerTest pinballOutputControllerTest(PinballOutputControllerTest::createTestController());
static LampMatrixTest lampMatrixTest(lampMatrix);

static Test& test = pinballOutputControllerTest;

void setup()
{
	test.setup();
}

void loop()
{
	test.loop();
}
