#ifndef UART_H
#define UART_H

#include <avr/io.h>

void uart_init();
void uart_putchar(char c);
void uart_println(const char* str, ...);
void uart_transmit(unsigned char data);

#endif // UART_H