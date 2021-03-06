MCU=attiny85
AVRDUDE_DEVICE=t85
F_CPU=1000000
OPTIMIZE=-Os
AVR_IO_INC=../../../avrIO/include
AVR_INT_INC=../../../avrINT/include

CXX=avr-g++
CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
INCLUDE=-I../../include -I$(AVR_IO_INC) -I$(AVR_INT_INC)
CXXFLAGS=-std=$(STD_CXX) -g -mmcu=$(MCU) -Wall -Wno-unused-variable -Wno-unused-but-set-variable $(OPTIMIZE) -DF_CPU=$(F_CPU) $(INCLUDE)

demos = read async_read gain

all: $(demos:%=%.elf) $(demos:%=%.lst) $(demos:%=%.s)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(demos:%=%.d)

%.s: %.cpp
	$(CXX) $(CXXFLAGS) -S $^

%.elf: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ 

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

.PHONY: flash_%
flash-%: %.hex
	avrdude -p $(AVRDUDE_DEVICE) -c usbasp -P usb  -U flash:w:$<

size:
	avr-size $(demos:%=%.elf)

.PHONY: clean
clean:
	rm -f *.hex *.lst *.elf *.o *.d *.s

