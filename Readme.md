# Embedded Projects

This repository contains various projects focused on low-level bare-metal programming using different microcontroller boards, including Arduino and ESP32. Each project is organized into its own subfolder, and the readme file within each subfolder provides more detailed information about the specific project.

## Project Structure

The repository is structured as follows:

- **atmega328p/**: Contains projects related to Arduino board.
  - **src/**: Source files for Arduino projects.
    - **drivers/**: Common modules used across different Arduino projects (e.g., ADC, I2C, LCD, UART).
    - **I2CMenueBasedSystem/**: Project for an I2C-based menu system using an LCD display and joystick for navigation.
  - **test/**: Test files for Arduino projects, organized for integration testing.
  - **build/**: Build artifacts and logs for Arduino projects.

- **esp32/**: Contains projects related to ESP32 boards.
  - **src/**: Source files for ESP32 projects.

- **Documentation/**: Contains documentation for the projects.
  - **atmega328p/**: Documentation specific to Arduino projects and drivers for Arduino board.
  - **readme.md**: Overview of the documentation folder.

## Overview

This repository is set up for low-level bare-metal and RTOS programming, providing detailed control over the hardware. The projects utilize different microcontroller boards, including Arduino and ESP32, each organized into its respective subfolder. The readme file within each subfolder provides more details about the specific project.

## Testing with Integration Tests

The projects are set up to handle testing using integration tests, as the code is dependent on hardware. Each subdirectory for the boards (Arduino, ESP32) includes a `test` folder containing test files. This setup ensures that the projects are thoroughly tested in an environment that closely mimics the actual hardware, maintaining high code quality.

## Project Subfolders

- **atmega328p/**: Contains projects related to Arduino boards.
  - **I2CMenueBasedSystem**: Contains a project related to an I2C-based menu subsystem with an LCD screen.

- **esp32/**: Contains projects related to ESP32 boards.
  - **httpserver**: Contains a project for an HTTP server running on the ESP32.
    - **src/**: Source files for the HTTP server project.
    - **ota/**: Implements Over-The-Air (OTA) firmware updates for the ESP32.

Feel free to explore each subfolder to find detailed information and code for each project. Stay tuned for more exciting projects that will be added to this repository.
