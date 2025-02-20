#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Common/helpers.h"

#define SHORT_PRESS_THRESHOLD 1000  // 2 seconds threshold
#define F_CPU 16000000UL  // ATmega328P runs at 16MHz
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

volatile uint16_t pressStartTime = 0;
volatile uint16_t pressDuration = 0;
volatile uint8_t buttonPressed = 0;

void setupTimer1() {
    // Configure Timer1 to count milliseconds
    TCCR1B |= (1 << CS11) | (1 << CS10);  // Prescaler = 64
    TIMSK1 |= (1 << TOIE1);  // Enable Timer1 overflow interrupt
}

void setupExternalInterrupt() {
    EICRA |= (1 << ISC00);   // Any logical change on INT0 triggers interrupt
    EIMSK |= (1 << INT0);    // Enable INT0 external interrupt
}

ISR(INT0_vect) {
    _delay_ms(50);  // Debounce delay
    if (!(PIND & (1 << PIND2))) {  // Button pressed (falling edge)
        pressStartTime = TCNT1;  // Capture Timer1 value
        buttonPressed = 1;
    } else {  // Button released (rising edge)
        pressDuration = (TCNT1 - pressStartTime) / (F_CPU / 64 / 1000); // Convert to ms
        buttonPressed = 0;

        if (pressDuration >= SHORT_PRESS_THRESHOLD) {
            // Long Press Action (e.g., print to serial)
            uart_println("long press! duration: %d ms", pressDuration);
        } else {
            // Short Press Action (e.g., print to serial)
            uart_println("short press! duration: %d ms", pressDuration);
        }
    }
}
    
ISR(TIMER1_OVF_vect) {
    // Timer overflow handling (not critical in this case)
}

int main(void) {
    uart_init(MYUBRR);     // Initialize UART
    setupTimer1();
    setupExternalInterrupt();
    sei();  // Enable global interrupts

    // Print initial message
    uart_println("Button Reading Started...");

    while (1) {
        // Main loop does nothing, actions handled in interrupts
    }
}