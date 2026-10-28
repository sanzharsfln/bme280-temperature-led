# Temperature-Controlled LED

Arduino Uno firmware that reads a BME280 temperature sensor and makes the built-in LED blink faster as the temperature rises. The project includes separate I2C and hardware SPI programs that share the same LED controller.

## Features

- Separate I2C and hardware SPI versions
- Temperature readings printed once per second at 115200 baud
- LED timing without blocking delays
- Separate sensor interfaces and LED control logic

## Blink Timing

| Temperature | Time between LED toggles |
|---|---|
| 25°C or below | 1,000 ms |
| 27.5°C | 550 ms |
| 30°C or above | 100 ms |

A complete on/off blink takes two toggles.

## Build

Open the project in VS Code with PlatformIO, then run:

```sh
pio run -e uno_i2c
pio run -e uno_spi
```

## Configuration

- **Board:** Arduino Uno
- **Sensor:** BME280
- **I2C address:** `0x76`
- **SPI chip-select pin:** D10
- **LED:** Built-in LED
