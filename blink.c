#include <util/delay.h>

#define BLINK_MS 150

// Define the memory-mapped registers for DDRB and PORTB
#define DDRB  (*(volatile unsigned char*)0x24)
#define PORTB (*(volatile unsigned char*)0x25)

// Define the bit for PB5 (pin 13 on Arduino Uno)
#define PB5 5

int main() {
    DDRB |= (1 << PB5);  // Set PB5 (pin 13) as output

    while (1) {
        PORTB ^= (1 << PB5);  // Toggle PB5 (pin 13)
        _delay_ms(BLINK_MS);  // Delay
    }

    return 0;
}