DEVICE=atmega328p
PROGRAMMER=arduino
PORT=/dev/tty.usbmodem1101
BAUD=115200

CC=avr-gcc -Wall -D F_CPU=16000000UL -Os -mmcu=$(DEVICE)

all: project

helpers.o: ../Common/helpers.c
	$(CC) -c ../Common/helpers.c -o helpers.o

i2c.o: ../Common/i2c.c
	$(CC) -c ../Common/i2c.c -o i2c.o

lcd.o: ../Common/lcd.c
	$(CC) -c ../Common/lcd.c -o lcd.o

project: project.o helpers.o i2c.o lcd.o
	$(CC) -o project.elf project.o helpers.o i2c.o lcd.o
	avr-objcopy -O ihex -R .eeprom project.elf project.hex
	avr-size --format=avr --mcu=$(DEVICE) project.elf

project.o: project.c
	$(CC) -c project.c -o project.o

installproject:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:project.hex:i

serialmonitor:
	screen $(PORT) 9600

clean:
	rm *.o *.elf *.hex