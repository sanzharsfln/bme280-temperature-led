#include <Arduino.h>
#include <math.h>
#include "BMEI2CInterface.h"
#include "LEDController.h"

bool sensorReady = false;
float temperatureC = NAN;
LEDController ledController;

void setup()
{
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    BMEI2CInterfaceInstance::create();

    sensorReady = BMEI2CInterfaceInstance::instance().begin();

    if (sensorReady)
    {
        Serial.println("BME280 initialized.");
        temperatureC = BMEI2CInterfaceInstance::instance().readTemperature();
    }
    else
    {
        Serial.println("BME280 initialization failed.");
    }
}

void loop()
{
    if (!sensorReady)
    {
        return;
    }

    static uint32_t lastReadMs = 0;
    uint32_t now = millis();

    if (now - lastReadMs >= 1000)
    {
        lastReadMs = now;

        auto& bme = BMEI2CInterfaceInstance::instance();
        temperatureC = bme.readTemperature();

        Serial.print("Temperature: ");
        Serial.print(temperatureC);
        Serial.println(" C");
    }

    ledController.update(temperatureC, now);
    digitalWrite(
        LED_BUILTIN,
        ledController.isOn() ? HIGH : LOW
    );
}
