#include <Arduino.h>
#include <math.h>
#include "BMESPIInterface.h"
#include "LEDController.h"

bool sensorReady = false;
float temperatureC = NAN;
LEDController ledController;

void setup()
{
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    BMESPIInterfaceInstance::create();
    auto& bme = BMESPIInterfaceInstance::instance();

    sensorReady = bme.begin();

    if (sensorReady)
    {
        Serial.println("BME280 initialized.");
        temperatureC = bme.readTemperature();
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

        auto& bme = BMESPIInterfaceInstance::instance();
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
