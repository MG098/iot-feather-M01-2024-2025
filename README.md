# Environmental Monitor

## Project Overview
Environmental Monitor is an advanced environmental monitoring system based on Arduino that collects and displays data from various environmental sensors.

## Features
The system measures and displays the following environmental parameters:
- Temperature
- Humidity
- Atmospheric pressure
- Light intensity (lux)

## Components
- Arduino microcontroller
- BME280 sensor (temperature, humidity, pressure)
- APDS9301 sensor (light intensity)
- 128x32 OLED display

## Project Architecture
The project is designed with a modular architecture, consisting of:
- Data structure (`sensor_data.h`)
- Sensor reading module (`sensor_reader.h/cpp`)
- Display management module (`display_manager.h/cpp`)
- Main configuration file (`main.cpp/hpp`)

## Key Functions
- Multi-layered sensor handling abstraction
- Dynamic environmental data reading
- Information display on OLED screen
- Simultaneous data logging to serial monitor

## Required Libraries
- Wire.h
- Adafruit_GFX
- Adafruit_SSD1306
- Adafruit_Sensor
- Adafruit_BME280
- Sparkfun_APDS9301_Library

## Setup
1. Connect sensors according to the diagram
2. Install required libraries
3. Upload code to Arduino

## Operation Mode
- Data reading every 2 seconds
- Display on OLED screen
- Simultaneous logging to serial monitor

## Expansion Possibilities
- Adding data logging to SD card
- Implementing wireless communication
- Extending the number of monitored parameters

## Wiring Diagram
```
Arduino Uno/Nano:
- BME280: I2C (A4/A5)
- APDS9301: I2C (A4/A5)
- OLED: I2C (A4/A5)
```

## Troubleshooting
- Check wire connection correctness
- Ensure all libraries are installed
- Verify I2C sensor addressing

## License
Open-source, allowed use and modification while preserving author information.

## Author
[Your Name]
Date of creation: [Date]

## Notes
The project requires basic knowledge of Arduino electronics and programming.
