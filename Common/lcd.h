#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

void lcd_send(uint8_t value, uint8_t mode);
void lcd_write_nibble(uint8_t nibble, uint8_t mode);
void lcd_enable_pulse(uint8_t data);
void lcd_init();
void lcd_print(const char *str);
void lcd_backlight_on();
void lcd_clear(); // Function to clear the screen

#endif // LCD_H
