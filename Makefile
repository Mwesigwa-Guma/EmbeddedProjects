all: menuproject

menuproject:
	$(MAKE) -C I2CMenueBasedSystem

cleanmenuproject:
	$(MAKE) -C I2CMenueBasedSystem clean

installmenuproject:
	$(MAKE) -C I2CMenueBasedSystem installproject

serialmonitor:
	screen $(PORT) 9600
