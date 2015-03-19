/*
 * CowZoneHardware.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: Dad
 */

#include "CowZoneHardware.h"

CowZoneHardware::CowZoneHardware() {
}

CowZoneHardware::~CowZoneHardware() {
}

static CowZoneHardware instance;
CowZoneHardware& CowZoneHardware::INSTANCE = instance;
