#include "i2c.h"

// Initialize the I2C interface
void i2c_init() {
    TWSR = 0x00; // Set prescaler to 1
    TWBR = 0x0C; // Set bit rate register (SCL frequency)
    TWCR = (1 << TWEN); // Enable TWI (Two Wire Interface)
}

// Send a start condition on the I2C bus
void i2c_start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send START condition
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set, indicating start condition has been transmitted
}

// Send a stop condition on the I2C bus
void i2c_stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // Send STOP condition
    while (TWCR & (1 << TWSTO)); // Wait for STOP condition to be executed and bus released
}

// Write a byte of data to the I2C bus
void i2c_write(uint8_t data) {
    TWDR = data; // Load data into TWDR register
    TWCR = (1 << TWEN) | (1 << TWINT); // Start transmission of data
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set, indicating data has been transmitted
}
