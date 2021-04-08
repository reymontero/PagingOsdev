OS:
	nasm -fbin Source/Bootloader/bootload.asm -o Obj/bootload.bin
	nasm -fbin Source/Bootloader/AfterBoot.asm -o Obj/boot.bin
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/kmain/kmain.c -o Obj/kmain.o
	nasm Source/Kernel/kmain/kmain.asm -f elf -o Obj/kentry.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/video/video.c -o Obj/video.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/math/math.c -o Obj/math.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/string/string.c -o Obj/string.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/IDT/IDT.c -o Obj/IDT.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/IDT/isr/isr.c -o Obj/isr.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/IDT/irq/irq.c -o Obj/irq.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/IO/io.c -o Obj/io.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/ps2/ps2.c -o Obj/ps2.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/ps2/keyboard/keyboard.c -o Obj/keyboard.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/ps2/mouse/mouse.c -o Obj/mouse.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/printf/printf.c -o Obj/printf.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/memory/memory.c -o Obj/memory.o
	
	gcc -mno-ms-bitfields -fno-PIC -m32 -ffreestanding -c Source/Kernel/memory/paging/paging.c -o Obj/paging.o
	nasm Source/Kernel/memory/paging/paging.asm -f elf -o Obj/pagingasm.o
	
	
	ld -T link.ld -o Obj/kernel.tmp Obj/kentry.o Obj/kmain.o Obj/video.o Obj/string.o Obj/math.o Obj/io.o Obj/ps2.o Obj/keyboard.o Obj/mouse.o Obj/IDT.o Obj/isr.o Obj/irq.o Obj/memory.o Obj/pagingasm.o Obj/paging.o Obj/printf.o 
	objcopy -O binary Obj/kernel.tmp Obj/kernel.bin

	
	
	
	copy /b "Obj\bootload.bin" + "Obj\boot.bin" + "Obj\kernel.bin" /b "Bin\os-image.bin"
	
	qemu-system-i386 -monitor stdio Bin/os-image.bin

clean:
	del Obj/*.o
	del Obj/*.temp
	del Obj/*.bin
