PHONY: compile list hex clean connect write

compile:
	avr-gcc -mmcu=atmega328p -Wall -Os -ggdb -o main.elf main.c

hex: compile
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

list: hex
	avr-objdump -S main.elf
	avr-objdump -m avr -D main.hex

connect:
	avrdude -p m328p -c usbasp
	avrdude -p m328p -c usbasp -P usb -v -U flash:r:flash_dump.hex:i

write: hex
	avrdude -p m328p -c usbasp -U flash:w:main.hex:i

clean:
	rm *.hex
	rm *.elf