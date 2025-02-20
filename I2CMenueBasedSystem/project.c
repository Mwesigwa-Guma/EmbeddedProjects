#include <avr/io.h>
#include <util/delay.h>
#include "../Common/i2c.h"
#include "../Common/lcd.h"

int main(void) {
    i2c_init(); // Initialize I2C communication
    lcd_init(); // Initialize LCD
    lcd_print("Hello, World!"); // Print message

    while (1) {
        // Infinite loop to keep the program running
    }

    return 0;
}
