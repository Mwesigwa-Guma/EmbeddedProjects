DEVICE=atmega328p
PROGRAMMER=arduino
PORT=/dev/tty.usbmodem*
BAUD=115200

CC=avr-gcc -Wall -D F_CPU=16000000UL -Os -mmcu=$(DEVICE)

all:installblink installtemperature

blink:blink.o
	$(CC) -o blink.elf blink.o
	avr-objcopy -O ihex -R .eeprom blink.elf blink.hex
	avr-size --format=avr --mcu=$(DEVICE) blink.elf

blink.o:blink.c
	$(CC) -c blink.c -o blink.o
	
temperature:temperature.o
	$(CC) -o temperature.elf temperature.o
	avr-objcopy -O ihex -R .eeprom temperature.elf temperature.hex
	avr-size --format=avr --mcu=$(DEVICE) temperature.elf

temperature.o:temperature.c
	$(CC) -c temperature.c -o temperature.o

installblink:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:blink.hex:i

installtemperature:
	avrdude -V -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:temperature.hex:i

clean:
	rm *.o *.elf *.hex