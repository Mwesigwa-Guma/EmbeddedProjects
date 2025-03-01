DEVICE=atmega328p
PROGRAMMER=arduino
PORT=/dev/tty.usbmodem1101
BAUD=115200

CC=avr-gcc -Wall -D F_CPU=16000000UL -Os -mmcu=$(DEVICE)

all: test_adc test_i2c test_lcd test_uart

test_i2c.o: test_i2c.c
	$(CC) -c test_i2c.c -o test_i2c.o

test_lcd.o: test_lcd.c
	$(CC) -c test_lcd.c -o test_lcd.o

test_uart.o: test_uart.c
	$(CC) -c test_uart.c -o test_uart.o

test_adc.o: test_adc.c
	$(CC) -c test_adc.c -o test_adc.o

test_adc: test_adc.o
	$(CC) -o test_adc.elf test_adc.o
	avr-objcopy -O ihex -R .eeprom test_adc.elf test_adc.hex
	avr-size --format=avr --mcu=$(DEVICE) test_adc.elf

test_uart: test_uart.o
	$(CC) -o test_uart.elf test_uart.o
	avr-objcopy -O ihex -R .eeprom test_uart.elf test_uart.hex
	avr-size --format=avr --mcu=$(DEVICE) test_uart.elf

test_lcd: test_lcd.o
	$(CC) -o test_lcd.elf test_lcd.o
	avr-objcopy -O ihex -R .eeprom test_lcd.elf test_lcd.hex
	avr-size --format=avr --mcu=$(DEVICE) test_lcd.elf

test_i2c: test_i2c.o
	$(CC) -o test_i2c.elf test_i2c.o
	avr-objcopy -O ihex -R .eeprom test_i2c.elf test_i2c.hex
	avr-size --format=avr --mcu=$(DEVICE) test_i2c.elf

installtestadc:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:test_adc.hex:i

installtestuart:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:test_uart.hex:i

installtestlcd:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:test_lcd.hex:i

installtesti2c:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:test_i2c.hex:i

clean:
	rm *.o *.elf *.hex