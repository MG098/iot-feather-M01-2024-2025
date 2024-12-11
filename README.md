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


