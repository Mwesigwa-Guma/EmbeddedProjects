DEVICE=atmega328p
PROGRAMMER=arduino
PORT=/dev/tty.usbmodem1101
BAUD=115200

CC=avr-gcc -Wall -D F_CPU=16000000UL -Os -mmcu=$(DEVICE)

%.o: %.c
	$(CC) -c $< -o $@

i2c.o: ../../src/Common/i2c.c
	$(CC) -c $< -o $@

lcd.o: ../../src/Common/lcd.c
	$(CC) -c $< -o $@

uart.o: ../../src/Common/uart.c
	$(CC) -c $< -o $@

adc.o: ../../src/Common/adc.c
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

install%:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$*.hex:i

clean:
	rm *.o *.elf *.hex