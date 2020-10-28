avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os "$@" -o a.elf
avr-objcopy -O ihex a.elf a.hex
rm a.elf
avrdude -c usbasp -p m644p -U flash:w:a.hex
rm a.hex
