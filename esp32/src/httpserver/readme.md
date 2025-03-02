# Setting Up ESP-IDF Locally

To set up the ESP-IDF development environment locally and use the `idf.py` command, follow these steps:

## Prerequisites

1. **Install Python**:
   Ensure you have Python installed. You can install it using Homebrew if it's not already installed:

   ```sh
   brew install python
   ```

## Installing ESP-IDF

1. **Install ESP-IDF and run setup script**:
   ```sh
   cd $HOME/esp
   rm -rf esp-idf
   git clone --recursive https://github.com/espressif/esp-idf.git
   cd esp-idf
   ./install.sh
   ```

## Setting Up Environment Variables

1. **Source the `export.sh` Script**:
   Source the `export.sh` script to set up the environment variables:
   ```sh
   source $HOME/esp/esp-idf/export.sh
   ```

## Using `idf.py`

After setting up the environment, you can use the `idf.py` command to build, flash, and monitor your ESP32 projects.

### Build the Project

To build the project, use the following command:
```sh
idf.py build
```

### Flash the Firmware

To flash the compiled firmware to the ESP32, use the following command:
```sh
idf.py flash
```

### Monitor the Serial Output

To monitor the serial output from the ESP32, use the following command:
```sh
idf.py monitor
```

### Quit the Serial Monitor

To quit the serial monitor, press the following key combination:
```sh
Ctrl + ]
```

### Example Workflow

1. **Build the Project**:
   ```sh
   idf.py build
   ```

2. **Flash the Firmware**:
   ```sh
   idf.py flash
   ```
   or
   
   ```sh
   idf.py -p /dev/tty.usbserial-110 flash monitor
   ```


3. **Monitor the Serial Output**:
   ```sh
   idf.py monitor
   ```

4. **Quit the Serial Monitor**:
   ```sh
   Ctrl + ]
   ```

This section provides a comprehensive guide on setting up the ESP-IDF development environment locally using Homebrew and using the `idf.py` command for building, flashing, and monitoring ESP32 projects.
