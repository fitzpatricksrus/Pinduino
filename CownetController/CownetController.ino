#include “WPCHardware.h"

void setup()
{
	//set up passthrough
	WPCHardware::INSTANCE.attachController(WPCHardware::PASSTHROUGH_CONTROLLER_INSTANCE);
}

void loop()
{
}
