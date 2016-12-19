PROJECT := microwwvb
MMCU := attiny44
PARTNO := t44
F_CPU := 20000000

SOURCES := $(PROJECT).c \
	serial.c \
	gps.c \

HEADERS := \
	serial.h \
	gps.h \
	hardware.h \

CFLAGS := -mmcu=$(MMCU) -Os -DF_CPU=$(F_CPU) -std=c99 \
	-Wall -Wextra -pedantic -Werror

$(PROJECT).hex: $(PROJECT).out
	avr-objcopy -O ihex $(PROJECT).out $(PROJECT).hex;\
	avr-size --mcu=$(MMCU) --format=avr $(PROJECT).out

$(PROJECT).out: $(SOURCES) $(HEADERS)
	avr-gcc $(CFLAGS) -o $(PROJECT).out $(SOURCES)

.PHONY: program-avrisp2
program-avrisp2: $(PROJECT).hex
	avrdude -p $(PARTNO) -P usb -c avrisp2 -U flash:w:$(PROJECT).hex

.PHONY: program-avrisp2-fuses
program-avrisp2-fuses:
	avrdude -p $(PARTNO) -P usb -c avrisp2 -U lfuse:w:0x5E:m

.PHONY: program-usbtiny
program-usbtiny: $(PROJECT).hex
	avrdude -p $(PARTNO) -P usb -c usbtiny -U flash:w:$(PROJECT).hex

.PHONY: program-usbtiny-fuses
program-usbtiny-fuses:
	avrdude -p $(PARTNO) -P usb -c usbtiny -U lfuse:w:0x5E:m

.PHONY: clean
clean:
	rm -rf $(PROJECT).out $(PROJECT).hex
