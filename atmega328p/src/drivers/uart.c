#include "uart.h"
#include <stdarg.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR ((F_CPU/16/BAUD)-1)

void uart_init() {
    // Set baud rate
    UBRR0H = (unsigned char)((MYUBRR) >> 8);
    UBRR0L = (unsigned char)(MYUBRR);
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_putchar(char c) {
    while (!(UCSR0A & (1 << UDRE0)));  // Wait for empty transmit buffer
    UDR0 = c;  // Put data into buffer, sends the data
}

void uart_transmit(unsigned char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    // Put data into buffer, sends the data
    UDR0 = data;
}

void uart_print(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    const char *str = buffer;
    while (*str) {
        uart_transmit(*str++);
    }
}

void uart_println(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    uart_print("%s\r\n", buffer);
}