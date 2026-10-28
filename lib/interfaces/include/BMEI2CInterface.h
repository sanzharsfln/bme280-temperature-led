#pragma once

#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class BMEI2CInterface
{
public:
    BMEI2CInterface() = default;

    bool begin();
    float readTemperature();

private:
    Adafruit_BME280 sensor;
};

using BMEI2CInterfaceInstance = etl::singleton<BMEI2CInterface>;
