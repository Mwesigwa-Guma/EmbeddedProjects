#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Common/i2c.h"
#include "../Common/lcd.h"
#include "../Common/adc.h"

#define JOYSTICK_X 0 // ADC channel for X-axis
#define JOYSTICK_Y 1 // ADC channel for Y-axis
#define JOYSTICK_BUTTON_PIN PD2 // Pin connected to joystick button
#define THRESHOLD 100

void button_init();
void update_menu(uint8_t cursor_position);
void initial_screen();
void led_init();
void led_stop();

// Global variables for menu items
const char menu_item_1[] = "Blink LED";
const char menu_item_2[] = "Turn on Buzzer";
const char item_1[] = "Blinking";
const char item_2[] = "Buzzing";

volatile uint8_t led_blinking = 0;

int main(void) {
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

    // Initial screen
    initial_screen();

    while (1) {
        // Read Y analog value from ADC channel
        uint16_t yValue = adc_read(JOYSTICK_Y); // Assuming VRY is connected to ADC1
        uint16_t xValue = adc_read(JOYSTICK_X); // Assuming VRX is connected to ADC0

        // Determine direction based on thresholds
        if (yValue < center - threshold) {
            cursor_position = 0;
        } else if (yValue > center + threshold) {
            cursor_position = 1;
        } else if (xValue > center + threshold) {
            initial_screen();
        }

        // Update cursor position
        lcd_set_cursor(cursor_position, 0);

        // Main loop does not need to handle button press
        // Button press is handled by ISR

        if (led_blinking)
            PORTB ^= (1 << PB5);  // Toggle PB5 (pin 13)

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

void initial_screen() {
    led_stop(); // Stop blinking before showing the initial screen
    lcd_clear();
    lcd_print_row(0, menu_item_1);
    lcd_print_row(1, menu_item_2);
    lcd_set_cursor(0, 0);
    lcd_show_cursor();
}

void led_init() {
    DDRB |= (1 << PB5);  // Set PB5 (pin 13) as output
    led_blinking = 1;
}

void led_stop() {
    // stop blinking 
    DDRB &= ~(1 << PB5);  // Set PB5 (pin 13) as input
    led_blinking = 0;
}

// Interrupt Service Routine for INT0
ISR(INT0_vect) {
    // Debounce delay
    _delay_ms(50);
    // Check if button is still pressed
    if (!(PIND & (1 << JOYSTICK_BUTTON_PIN))) {
        // Check cursor position and display the corresponding item
        if (lcd_get_cursor_row() == 0) {
            led_init();
            lcd_clear();
            lcd_print_row(0, item_1);
        } else if (lcd_get_cursor_row() == 1) {
            lcd_clear();
            lcd_print_row(1, item_2);
        }
    }
}