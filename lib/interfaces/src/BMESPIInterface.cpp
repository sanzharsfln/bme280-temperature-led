#include "BMESPIInterface.h"

bool BMESPIInterface::begin()
{
    return sensor.begin();
}

float BMESPIInterface::readTemperature()
{
    return sensor.readTemperature();
}
