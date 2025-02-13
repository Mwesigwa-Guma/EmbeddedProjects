#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "Common/serial.h"

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

int main(void) {
    // Initialize UART
    uart_init(MYUBRR);

    // Set pin 7 as input
    DDRD &= ~(1 << PD2);

    // Configure INT0 (PD2) to trigger on falling edge
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);

    sei();

    // Print initial message
    uart_println("Button Reading Started...");

    // Main loop
    while (1) {
        // Do nothing
    }

    return 0;
}

// Interrupt Service Routine for INT0
ISR(INT0_vect) {
    uart_println("Button pressed!");
    // Small delay to debounce the button
        _delay_ms(150);
}