DEVICE=atmega328p
PROGRAMMER=arduino
PORT=/dev/tty.usbmodem1101
BAUD=115200
SRCDIR=../../src/Common

CC=avr-gcc -Wall -D F_CPU=16000000UL -Os -mmcu=$(DEVICE)
OBJS = test_i2c.o test_lcd.o test_uart.o test_adc.o adc.o uart.o i2c.o lcd.o

%.o: %.c
	$(CC) -c $< -o $@

adc.o: $(SRCDIR)/adc.c
	$(CC) -c $< -o $@

uart.o: $(SRCDIR)/uart.c
	$(CC) -c $< -o $@

i2c.o: $(SRCDIR)/i2c.c
	$(CC) -c $< -o $@

lcd.o: $(SRCDIR)/lcd.c
	$(CC) -c $< -o $@

test_adc: test_adc.o adc.o uart.o
	$(CC) -o $@.elf $^
	avr-objcopy -O ihex -R .eeprom $@.elf $@.hex
	avr-size --format=avr --mcu=$(DEVICE) $@.elf

test_uart: test_uart.o uart.o
	$(CC) -o $@.elf $^
	avr-objcopy -O ihex -R .eeprom $@.elf $@.hex
	avr-size --format=avr --mcu=$(DEVICE) $@.elf

test_lcd: test_lcd.o lcd.o uart.o i2c.o
	$(CC) -o $@.elf $^
	avr-objcopy -O ihex -R .eeprom $@.elf $@.hex
	avr-size --format=avr --mcu=$(DEVICE) $@.elf

test_i2c: test_i2c.o i2c.o uart.o
	$(CC) -o $@.elf $^
	avr-objcopy -O ihex -R .eeprom $@.elf $@.hex
	avr-size --format=avr --mcu=$(DEVICE) $@.elf

flash:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:*.hex:i

clean:
	rm -f $(OBJS) *.elf *.hex