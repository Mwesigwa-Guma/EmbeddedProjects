#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Common/helpers.h"

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define DHT11_PIN 7

uint8_t read_dht11(uint8_t *temperature, uint8_t *humidity);

int main(void) {
    // Initialize UART
    uart_init(MYUBRR);

    // Main loop
    while (1) {
        uint8_t temperature = 0;
        uint8_t humidity = 0;

        if (read_dht11(&temperature, &humidity)) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "Temperature: %dC, Humidity: %d%%\r\n", temperature, humidity);
            uart_print(buffer);
        } else {
            uart_print("Error reading from DHT11 sensor\r\n");
        }

        // Wait a bit before reading again
        _delay_ms(2000);
    }

    return 0;
}

uint8_t read_dht11(uint8_t *temperature, uint8_t *humidity) {
    uint8_t bits[5];
    uint8_t i, j = 0;

    // Reset bits
    for (i = 0; i < 5; i++) bits[i] = 0;

    // Request sample
    DDRD |= (1 << DHT11_PIN); // Set pin as output
    PORTD &= ~(1 << DHT11_PIN); // Set pin low
    _delay_ms(18);
    PORTD |= (1 << DHT11_PIN); // Set pin high
    _delay_us(40);
    DDRD &= ~(1 << DHT11_PIN); // Set pin as input

    // Wait for response
    _delay_us(80);
    if (PIND & (1 << DHT11_PIN)) return 0;
    _delay_us(80);
    if (!(PIND & (1 << DHT11_PIN))) return 0;
    _delay_us(80);

    // Read data
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 8; i++) {
            while (!(PIND & (1 << DHT11_PIN))); // Wait for pin to go high
            
            _delay_us(30);

            if (PIND & (1 << DHT11_PIN)) 
                bits[j] |= (1 << (7 - i));

            while (PIND & (1 << DHT11_PIN)); // Wait for pin to go low
        }
    }

    // Checksum
    if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) return 0;

    *humidity = bits[0];
    *temperature = bits[2];

    return 1;
}