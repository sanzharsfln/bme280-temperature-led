#pragma once

#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class BMESPIInterface
{
public:
    BMESPIInterface()
        : sensor(BMEConstants::SPI_CS_PIN)
    {
    }

    bool begin();
    float readTemperature();

private:
    Adafruit_BME280 sensor;
};

using BMESPIInterfaceInstance =
    etl::singleton<BMESPIInterface>;
