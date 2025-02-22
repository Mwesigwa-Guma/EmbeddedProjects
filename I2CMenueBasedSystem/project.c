#include <avr/io.h>
#include <util/delay.h>
#include "../Common/i2c.h"
#include "../Common/lcd.h"
#include "../Common/uart.h"

#define JOYSTICK_X 0 // ADC channel for X-axis
#define JOYSTICK_Y 1 // ADC channel for Y-axis
#define THRESHOLD 100

void adc_init();
uint16_t adc_read(uint8_t channel);

int main(void) {
    // Initialize UART
    adc_init(); // Initialize ADC

    // Initialize I2C and LCD
    i2c_init();
    lcd_init();

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

        _delay_ms(200); // Delay for readability
    }

    return 0;
}

void adc_init() {
    // Reference voltage: AVcc, ADC prescaler: 128
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t channel) {
    // Select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
    return ADC;
}