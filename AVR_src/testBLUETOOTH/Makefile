TARGET = atmega168p
F_CPU = 8000000
COMPILE = avr-gcc -Wall -O2  -I. -DF_CPU=$(F_CPU) -mmcu=$(TARGET) # -DDEBUG_LEVEL=2

OBJECTS =  main.o


all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

clean:
	rm -f main.hex main.lst main.obj main.cof main.list main.map main.eep.hex main.bin *.o main.s 

main.bin:	$(OBJECTS)
	$(COMPILE) -o main.bin $(OBJECTS) -Wl,-Map,main.map

main.hex:	main.bin
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex

cpp:
	$(COMPILE) -E main.c

flash:
	avrdude -c toku1938 -p $(TARGET) -P ft0 -u -U flash:w:main.hex
fuses:
	avrdude -c toku1938 -p $(TARGET) -P ft0 -U hfuse:w:0xdf:m -U lfuse:w:0xe2:m -B 38400
