# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: kernel_entry.o kernel.o
	E:\\i686-elf-tools-windows\\bin\\i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: kernel_entry.asm
	C:\\Users\\jussi\\AppData\\Local\\bin\\NASM\\nasm $< -f elf -o $@

kernel.o: kernel.c
	E:\\i686-elf-tools-windows\\bin\\i686-elf-gcc -ffreestanding -c $< -o $@

# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	C:\\Users\\jussi\\AppData\\Local\\bin\\NASM\\ndisasm -b 32 $< > $@

bootsect.bin: bootsect.asm
	C:\\Users\\jussi\\AppData\\Local\\bin\\NASM\\nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	E:\\2e\\qemu\\qemu-system-i386 -fda $<

clean:
	rm *.bin *.o *.dis
