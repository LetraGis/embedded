CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS=-c -mcpu=$(MACH) -std=gnu11 -mthumb -Wall -O0 -g
LDFLAGS=-nostdlib -T stm32_ls.ld -Wl,-Map=output.map
DISS=arm-none-eabi-objdump -S --disassemble output.elf > output.s


all: main.o stm32_startup.o other.o output.elf diss
 
# main.o: main.c
# 	$(CC) $(CFLAGS) -o $@ $^

# stm32_startup.o: stm32_startup.c
# 	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

output.elf: main.o stm32_startup.o other.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf *.s

diss:
	$(DISS)

load: 
	openocd -f board/st_nucleo_f4.cfg