cpu ?= cortex-m3
board ?= stm32vldiscovery

.PHONY = qemu gdb compile clean objdump
CFLAGS = -mcpu=$(cpu) -mthumb -g -ffreestanding -nostdlib

start.s: start.c
	arm-none-eabi-gcc -S -mthumb -mcpu=$(cpu) $< -o $@


start.o: start.c
	arm-none-eabi-gcc -c -mthumb -mcpu=$(cpu) $< -o $@

boot.o: boot.S
	arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb -g -ffreestanding -nostdlib boot.S -o boot.o

boot.elf: boot.o start.o
	arm-none-eabi-ld -T link.ld $^ -o $@

objdump:
	arm-none-eabi-objdump -S boot.o > boot.elf.lst
	arm-none-eabi-readelf -a boot.elf > main.elf.debug

qemu:
	qemu-system-arm -S -gdb tcp::1234 -M $(board) -cpu $(cpu) -nographic -kernel boot.elf

gdb:
	gdb-multiarch -q boot.elf -ex "target remote localhost:1234"

clean:
	rm -rf *.o *.elf