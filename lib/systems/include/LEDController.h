#pragma once

#include <stdint.h>

class LEDController
{
public:
    void update(float temperatureC, uint32_t nowMs);
    bool isOn() const;

private:
    bool ledOn = false;
    uint32_t lastToggleMs = 0;
};
