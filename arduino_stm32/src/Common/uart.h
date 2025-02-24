#ifndef UART_H
#define UART_H

#include <avr/io.h>

void uart_init(unsigned int ubrr);
void uart_putchar(char c);
void uart_println(const char* str, ...);

#endif // UART_H