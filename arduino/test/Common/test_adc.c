#include <avr/io.h>
#include <util/delay.h>
#include "../../src/Common/adc.h"
#include "../../src/Common/uart.h"

void test_adc_init() {
    adc_init();

    // Check if ADMUX and ADCSRA are configured correctly
    if ((ADMUX == (1 << REFS0)) && (ADCSRA == ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)))) {
        uart_println("ADC Init: PASSED\n");
    } else {
        uart_println("ADC Init: FAILED\n");
    }
}

void test_adc_read() {
    uint8_t test_channel = 0; // Read from ADC channel 0 (assume a known voltage)
    uint16_t adc_value = adc_read(test_channel);

    // Expected ADC range (assuming 10-bit ADC and 5V reference)
    if (adc_value >= 0 && adc_value <= 1023) {
        uart_println("ADC Read (Channel %d): PASSED, Value: %d\n", test_channel, adc_value);
    } else {
        uart_println("ADC Read (Channel %d): FAILED, Value: %d\n", test_channel, adc_value);
    }
}

void test_adc_accuracy() {
    uint8_t test_channel = 0;
    uint16_t adc_value = adc_read(test_channel);
    
    // Convert ADC value to voltage (assuming 5V reference)
    float voltage = (adc_value / 1023.0) * 5.0;

    // Assume input voltage should be around 2.5V (if using a voltage divider)
    if (voltage >= 2.4 && voltage <= 2.6) {
        uart_println("ADC Accuracy Test: PASSED (%.2f V)\n", voltage);
    } else {
        uart_println("ADC Accuracy Test: FAILED (%.2f V)\n", voltage);
    }
}

int main() {
    uart_init();  // Initialize UART for debugging
    _delay_ms(1000); // Wait for stability

    test_adc_init();
    test_adc_read();
    test_adc_accuracy();

    while (1);
}