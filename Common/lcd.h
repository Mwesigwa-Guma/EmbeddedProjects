#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

void lcd_send(uint8_t value, uint8_t mode);
void lcd_write_nibble(uint8_t nibble, uint8_t mode);
void lcd_enable_pulse(uint8_t data);
void lcd_init();
void lcd_print(const char *str);
void lcd_print_row(uint8_t row, const char *str); // Function to print to a specific row
void lcd_backlight_on();
void lcd_clear(); // Function to clear the screen
void lcd_set_cursor(uint8_t row, uint8_t col); // Function to set the cursor position
void lcd_show_cursor(); // Function to show the cursor
void lcd_hide_cursor(); // Function to hide the cursor
uint8_t lcd_get_cursor_row(); // Function to get the cursor row
uint8_t lcd_get_cursor_col(); // Function to get the cursor column

#endif // LCD_H
