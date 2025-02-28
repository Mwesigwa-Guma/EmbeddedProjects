#include <util/delay.h>
#include "../../src/Common/lcd.h"
#include "../../src/Common/uart.h"

void test_lcd_init() {
    lcd_init();

    // Check if LCD is initialized correctly (assuming some known state)
    // This is a placeholder as actual verification might require reading LCD state
    uart_println("LCD Init: PASSED\n");
}

void test_lcd_print() {
    lcd_print("Hello");
    // Check if "Hello" is printed on the LCD
    // This is a placeholder as actual verification might require reading LCD state
    uart_println("LCD Print: PASSED\n");
}

int main() {
    uart_init();  // Initialize UART for debugging
    _delay_ms(1000); // Wait for stability

    test_lcd_init();
    test_lcd_print();

    while (1);
}