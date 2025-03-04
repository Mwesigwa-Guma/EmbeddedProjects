#include <avr/io.h>
#include <util/delay.h>
#include "../../src/Common/i2c.h"
#include "../../src/Common/uart.h"

void test_i2c_init() {
    i2c_init();

    // Check if TWBR and TWSR are configured correctly
    if (TWBR == ((F_CPU / 100000UL) - 16) / 2 && (TWSR & ((1 << TWPS1) | (1 << TWPS0))) == 0) {
        uart_println("I2C Init: PASSED\n");
    } else {
        uart_println("I2C Init: FAILED\n");
    }
}

void test_i2c_start() {
    i2c_start();
    // Check if the start condition was transmitted
    if ((TWSR & 0xF8) == 0x08) {
        uart_println("I2C Start: PASSED\n");
    } else {
        uart_println("I2C Start: FAILED\n");
    }
}

int main() {
    uart_init();  // Initialize UART for debugging
    _delay_ms(1000); // Wait for stability

    test_i2c_init();
    test_i2c_start();

    while (1);
}