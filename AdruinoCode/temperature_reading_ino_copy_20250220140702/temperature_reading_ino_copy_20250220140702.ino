#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x3F  // I2C address of the LCD (Change to 0x27 if needed)

LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2); // Set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
    lcd.init(); // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    lcd.print("Hello, World!"); // Print message
}

void loop() {
    // Nothing needed here, message remains on screen
}
