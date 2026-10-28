#include "LEDController.h"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>

void checkTiming(float temperature, uint32_t interval)
{
    LEDController controller;
    controller.update(temperature, 0);
    assert(!controller.isOn());
    controller.update(temperature, interval - 1);
    assert(!controller.isOn());
    controller.update(temperature, interval);
    assert(controller.isOn());
    controller.update(temperature, 2 * interval - 1);
    assert(controller.isOn());
    controller.update(temperature, 2 * interval);
    assert(!controller.isOn());
}

int main()
{
    checkTiming(25.0f, 1000);
    checkTiming(27.5f, 550);
    checkTiming(30.0f, 100);
    checkTiming(-40.0f, 1000);
    checkTiming(85.0f, 100);

    for (float invalid : {NAN, INFINITY, -INFINITY})
    {
        LEDController controller;
        controller.update(30.0f, 100);
        assert(controller.isOn());
        controller.update(invalid, 150);
        assert(!controller.isOn());
        controller.update(30.0f, 249);
        assert(!controller.isOn());
        controller.update(30.0f, 250);
        assert(controller.isOn());
    }

    LEDController rollover;
    const uint32_t start = UINT32_MAX - 49;
    rollover.update(30.0f, start);
    assert(rollover.isOn());
    rollover.update(30.0f, 49);
    assert(rollover.isOn());
    rollover.update(30.0f, 50);
    assert(!rollover.isOn());

    LEDController changing;
    changing.update(25.0f, 500);
    assert(!changing.isOn());
    changing.update(30.0f, 501);
    assert(changing.isOn());
    changing.update(25.0f, 1500);
    assert(changing.isOn());
    changing.update(25.0f, 1501);
    assert(!changing.isOn());

    std::cout << "PASS: timing, temperature limits, invalid readings and recovery, "
                 "timer rollover, warming and cooling.\n";
}
