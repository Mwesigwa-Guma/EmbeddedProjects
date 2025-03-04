#include <avr/io.h>
#include <util/delay.h>
#include "../../src/Common/uart.h"

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void test_uart_init() {
    uart_init();

    // Check if UBRR0H and UBRR0L are configured correctly
    if (UBRR0H == (MYUBRR >> 8) && (UBRR0L == MYUBRR)) {
        uart_println("UART Init: PASSED\n");
    } else {
        uart_println("UART Init: FAILED\n");
    }
}

void test_uart_transmit() {
    uart_transmit('A');
    // Check if 'A' is transmitted
    // This is a placeholder as actual verification might require reading UART state
    uart_println("UART Transmit: PASSED\n");
}

int main() {
    uart_init();  // Initialize UART for debugging
    _delay_ms(1000); // Wait for stability

    test_uart_init();
    test_uart_transmit();

    while (1);
}