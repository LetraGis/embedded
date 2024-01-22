CC=arm-none-eabi-gcc
MACH=cortex-m4
# LNK=-specs=nosys.specs -specs=nano.specs -specs=rdimon.specs -lc -lrdimon
LNK= -specs=rdimon.specs -lc -lrdimon
CFLAGS=-c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 -g
LDFLAGS=-mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map
LDFLAGS_SEMIHOST= -mcpu=$(MACH) -mthumb -mfloat-abi=soft $(LNK) -T stm32_ls.ld -Wl,-Map=final.map
DISS=arm-none-eabi-objdump -S --disassemble output.elf > output.s

all: main.o stm32_startup.o other.o syscalls.o output.elf diss

semi: main.o stm32_startup.o other.o output_sh.elf

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

output.elf: main.o stm32_startup.o other.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

output_sh.elf: main.o stm32_startup.o other.o
	$(CC) $(LDFLAGS_SEMIHOST) -o $@ $^

clean:
	rm -rf *.o *.elf *.s

diss:
	$(DISS)

load: 
	openocd -f board/st_nucleo_f4.cfg