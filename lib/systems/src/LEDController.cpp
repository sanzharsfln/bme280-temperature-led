#include "LEDController.h"
#include <math.h>

void LEDController::update(float temperatureC, uint32_t nowMs)
{
    if (!isfinite(temperatureC))
    {
        ledOn = false;
        lastToggleMs = nowMs;
        return;
    }

    // 25 C gives slow blinking; 30 C gives fast blinking.
    float fraction = (temperatureC - 25.0f) / 5.0f;

    if (fraction < 0.0f)
    {
        fraction = 0.0f;
    }
    else if (fraction > 1.0f)
    {
        fraction = 1.0f;
    }

    uint32_t intervalMs =
        static_cast<uint32_t>(1000.0f - fraction * 900.0f);

    if (nowMs - lastToggleMs >= intervalMs)
    {
        ledOn = !ledOn;
        lastToggleMs = nowMs;
    }
}

bool LEDController::isOn() const
{
    return ledOn;
}
