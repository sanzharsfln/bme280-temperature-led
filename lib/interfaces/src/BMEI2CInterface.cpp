#include "BMEI2CInterface.h"

bool BMEI2CInterface::begin()
{
    return sensor.begin(0x76);
}

float BMEI2CInterface::readTemperature()
{
    return sensor.readTemperature();
}
