#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Common/i2c.h"
#include "../Common/lcd.h"
#include "../Common/uart.h"
#include "../Common/adc.h"

#define JOYSTICK_X 0 // ADC channel for X-axis
#define JOYSTICK_Y 1 // ADC channel for Y-axis
#define JOYSTICK_BUTTON_PIN PD2 // Pin connected to joystick button
#define THRESHOLD 100

void button_init();

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

    // Enable global interrupts
    sei();

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

        // Main loop does not need to handle button press
        // Button press is handled by ISR

        _delay_ms(200); // Delay for readability
    }

    return 0;
}

void button_init() {
    // Set button pin as input
    DDRD &= ~(1 << JOYSTICK_BUTTON_PIN);
    // Enable pull-up resistor
    PORTD |= (1 << JOYSTICK_BUTTON_PIN);

    // Enable external interrupt on INT0 (PD2)
    EICRA |= (1 << ISC01); // Trigger on falling edge
    EIMSK |= (1 << INT0);  // Enable INT0
}

// Interrupt Service Routine for INT0
ISR(INT0_vect) {
    // Debounce delay
    _delay_ms(50);
    // Check if button is still pressed
    if (!(PIND & (1 << JOYSTICK_BUTTON_PIN))) {
        uart_println("Button pressed");
    }
}