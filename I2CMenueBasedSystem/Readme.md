This project aims to develop an I2C-based menu system using an LCD display and a joystick or buttons for navigation. The system will allow users to interact with multiple menu screens and adjust various parameters, such as brightness and alarm time.

## Components
- **LCD Display (I2C Interface)**: To display menu options and settings.
- **Joystick or Buttons**: For navigating and selecting menu items.
- **Microcontroller (Arduino Uno R3 or compatible)**: To manage UI logic and process inputs.

## Functional Requirements

### Core Features
- Multi-screen navigation using the joystick or buttons.
- Adjustable values such as brightness and alarm time.
- State machine implementation to manage menu interactions.

### Challenges and Enhancements
- EEPROM storage for retaining settings after power loss.
- Dynamic menu rendering based on user interaction.

## How to Build the Project

### Prerequisites
- **Arduino IDE** or **PlatformIO** installed.
- **avr-gcc** and **avrdude** installed.
- **Make** utility installed.

### Steps to Build

1. **Clone the Repository**:

   ```sh
   cd I2CMenueBasedSystem
   make
   make installproject
   ```
