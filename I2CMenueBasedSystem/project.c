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
void update_menu(uint8_t cursor_position);

// Global variables for menu items
const char menu_item_1[] = "First item";
const char menu_item_2[] = "Second item";
const char item_1[] = "First selected";
const char item_2[] = "Second selected";

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
    uint8_t cursor_position = 0;

    // Enable global interrupts
    sei();

    // Initial menu display
    lcd_clear();
    lcd_print_row(0, menu_item_1);
    lcd_print_row(1, menu_item_2);
    lcd_set_cursor(0, 0);
    lcd_show_cursor();

    while (1) {
        // Read Y analog value from ADC channel
        uint16_t yValue = adc_read(JOYSTICK_Y); // Assuming VRY is connected to ADC1

        // Determine direction based on thresholds
        if (yValue < center - threshold) {
            cursor_position = 0;
        } else if (yValue > center + threshold) {
            cursor_position = 1;
        }

        // Update cursor position
        lcd_set_cursor(cursor_position, 0);

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

        // Check cursor position and display the corresponding item
        if (lcd_get_cursor_row() == 0) {
            lcd_clear();
            lcd_print_row(0, item_1);
        } else if (lcd_get_cursor_row() == 1) {
            lcd_clear();
            lcd_print_row(0, item_2);
        }
    }
}