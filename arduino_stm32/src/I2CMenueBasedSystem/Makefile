DEVICE=atmega328p
PROGRAMMER=arduino
PORT=/dev/tty.usbmodem1101
BAUD=115200

CC=avr-gcc -Wall -D F_CPU=16000000UL -Os -mmcu=$(DEVICE)

all: project

i2c.o: ../Common/i2c.c
	$(CC) -c ../Common/i2c.c -o i2c.o

lcd.o: ../Common/lcd.c
	$(CC) -c ../Common/lcd.c -o lcd.o

uart.o: ../Common/uart.c
	$(CC) -c ../Common/uart.c -o uart.o

adc.o: ../Common/adc.c
	$(CC) -c ../Common/adc.c -o adc.o

project: project.o i2c.o lcd.o uart.o adc.o
	$(CC) -o project.elf project.o i2c.o lcd.o uart.o adc.o
	avr-objcopy -O ihex -R .eeprom project.elf project.hex
	avr-size --format=avr --mcu=$(DEVICE) project.elf

project.o: project.c
	$(CC) -c project.c -o project.o

installproject:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:project.hex:i

clean:
	rm *.o *.elf *.hex