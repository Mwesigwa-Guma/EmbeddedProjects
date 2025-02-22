#include <avr/io.h>
#include <util/delay.h>
#include "../Common/i2c.h"
#include "../Common/lcd.h"
#include "../Common/uart.h"
#include "../Common/adc.h"

#define JOYSTICK_X 0 // ADC channel for X-axis
#define JOYSTICK_Y 1 // ADC channel for Y-axis
#define JOYSTICK_BUTTON_PIN PD2
#define THRESHOLD 100

void button_init();
uint8_t button_read();

int main(void) {
    // Initialize UART
    uart_init(103); // 9600 baud rate for 16MHz clock
    uart_println("Button test");

    // Initialize ADC, I2C, and LCD
    adc_init();
    i2c_init();
    lcd_init();
    button_init();

    const uint16_t threshold = 200;
    const uint16_t center = 512;

    while (1) {
        // Read Y analog value from ADC channel
        uint16_t yValue = adc_read(JOYSTICK_Y); // Assuming VRY is connected to ADC1

        // Determine direction based on thresholds
        if (yValue < center - threshold) {
            lcd_clear();
            lcd_print("first item");
        } else if (yValue > center + threshold) {
            lcd_clear();
            lcd_print("second item");
        }

        // Read joystick button state
        if (button_read() == 0) { // Button pressed
            uart_println("Button pressed");
        }

        _delay_ms(200); // Delay for readability
    }

    return 0;
}

void button_init() {
    DDRD &= ~(1 << JOYSTICK_BUTTON_PIN); // Set button pin as input
    PORTD |= (1 << JOYSTICK_BUTTON_PIN); // Enable pull-up resistor
}

uint8_t button_read() {
    return PIND & (1 << JOYSTICK_BUTTON_PIN); // Read button state
}