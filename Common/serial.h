#include <avr/io.h>

void uart_init(unsigned int ubrr);
void uart_transmit(unsigned char data);
void uart_print(const char *str);
void uart_println(const char *str);
