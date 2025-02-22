PORT=/dev/tty.usbmodem1101

all: menuproject

menuproject:
	$(MAKE) -C I2CMenueBasedSystem

cleanmenuproject:
	$(MAKE) -C I2CMenueBasedSystem clean

installmenuproject:
	$(MAKE) -C I2CMenueBasedSystem installproject

clean:
	$(MAKE) -C I2CMenueBasedSystem clean

sermon:
	screen $(PORT) 9600
