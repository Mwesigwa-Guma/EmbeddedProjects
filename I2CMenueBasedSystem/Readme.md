This project develops an I2C-based menu system using an LCD display and a joystick for navigation. The system allows users to interact with a menu screen with two options, Blink LED or Turn on Buzzer. An LED will start blinking if that's the option chosen and the screen displays "Blinking" to reflect the action. Similarly, if user chooses, Turn on Buzzer, the buzzer is turned on and screen displays current action.

This project is a bare-metal, standalone system aimed at learning various aspects of embedded programming. It involves serial communication with UART and I2C, interrupt handling, testing, and analog-to-digital input conversion.

## Components
- **LCD Display (I2C Interface)**: To display menu options and settings.
- **Joystick or Buttons**: For navigating and selecting menu items.
- **Microcontroller (Arduino Uno R3 or compatible)**: To manage UI logic and process inputs.

## Functional Requirements

### Core Features
- screen navigation using the joystick.
- choose between tow options, blinking and led or turning on buzzer.
- State machine implementation to manage menu interactions.

### Challenges and Enhancements
- EEPROM storage for retaining settings after power loss.
- Muti-screen menu in stead of just one with two items

## How to Build the Project

### Prerequisites
- **avr-gcc** and **avrdude** installed.
- **Make** utility installed.

### Steps to Build

1. **Clone the Repository**:

   ```sh
   cd I2CMenueBasedSystem
   make
   make installproject
   ```
