
#include "IDT.h"



/* Common body for interrupt handler */
#define MAKE_INTERRUPT_COMMON_STUB(intno, intfunc) \
			"push $"#intno"\n\t" \
			"pusha\n\t" \
			"push %ds\n\t" \
			"push %es\n\t" \
			"push %fs\n\t" \
			"push %gs\n\t" \
			"mov $0x10, %eax\n\t"   /* Set the segments to kernel data selector*/ \
			"mov %eax, %ds\n\t" \
			"mov %eax, %es\n\t" \
			"mov %eax, %fs\n\t" \
			"mov %eax, %gs\n\t" \
			"cld\n\t" \
			"push %esp\n\t" \
			"call _" #intfunc "\n\t" \
			"pop %eax\n\t" \
			"pop %gs\n\t" \
			"pop %fs\n\t" \
			"pop %es\n\t" \
			"pop %ds\n\t" \
			"popa\n\t" \
			"add $8, %esp\n\t"       /* Skip int_num and err_code */ \
			"iret\n\t" \
			"#.popsection\n\t"

/* Make interrupt for exception without error code. Push a dummy value for the
 * error code in it place. Push all the segment registers and the segment registers
 * so that they are available to interrupt function (intfun). Pushes a unique
 * interrupt number (intno) after the error code so that a handler can be multiplexed
 * if needed. Restore all the registers upon exit.
 *
 * intentry: Is the interrupt entry point that can be used in an Interrupt
 *           Descriptor Table (IDT) entry.
 * intfunc:  Is the C interrupt function that the stub calls to do processing
 * intno:    Interrupt number. Can be used to multiplex multiple interrupts to one
 *           intfunc handler.
 */
#define MAKE_INTERRUPT(intentry, intfunc, intno) \
	extern void intentry (void); \
	__asm__("#.pushsection .text\n\t" \
			".global _" #intentry "\n\t" \
			".align 16\n\t" \
			"_" #intentry ":\n\t" \
			"push $0\n\t"            /* Push dummy error code */ \
			MAKE_INTERRUPT_COMMON_STUB(intno, intfunc));

/* Make interrupt for exception with error code. Processor pushes the error code
 * after the return address automatically. Push all the segment registers and the
 * segment registers so that they are available to interrupt function (intfun).
 * Pushes a unique interrupt number (intno) after the error code so that a handler
 * can be multiplexed if needed. Restore all the registers upon exit.
 *
 * intentry: Is the interrupt entry point that can be used in an Interrupt
 *           Descriptor Table (IDT) entry.
 * intfunc:  Is the C interrupt function that the stub calls to do processing
 * intno:    Interrupt number. Can be used to multiplex multiple interrupts to one
 *           intfunc handler.
*/
#define MAKE_INTERRUPT_ERRCODE(intentry, intfunc, intno) \
	extern void intentry (void); \
	__asm__("#.pushsection .text\n\t" \
			".global _" #intentry "\n" \
			".align 16\n\t" \
			"_" #intentry ":\n\t" \
			MAKE_INTERRUPT_COMMON_STUB(intno, intfunc));

MAKE_INTERRUPT        (isr0,  isr0_handler,  0x00)
MAKE_INTERRUPT        (isr1,  isr1_handler,  0x01)
MAKE_INTERRUPT        (isr2,  isr2_handler,  0x02)
MAKE_INTERRUPT        (isr3,  isr3_handler,  0x03)
MAKE_INTERRUPT        (isr4,  isr4_handler,  0x04)
MAKE_INTERRUPT        (isr5,  isr5_handler,  0x05)
MAKE_INTERRUPT        (isr6,  isr6_handler,  0x06)
MAKE_INTERRUPT        (isr7,  isr7_handler,  0x07)
MAKE_INTERRUPT_ERRCODE(isr8,  isr8_handler,  0x08)
MAKE_INTERRUPT        (isr9,  isr9_handler,  0x09)
MAKE_INTERRUPT_ERRCODE(isr10, isr10_handler, 0x0a)
MAKE_INTERRUPT_ERRCODE(isr11, isr11_handler, 0x0b)
MAKE_INTERRUPT_ERRCODE(isr12, isr12_handler, 0x0c)
MAKE_INTERRUPT_ERRCODE(isr13, isr13_handler, 0x0d)
MAKE_INTERRUPT_ERRCODE(isr14, isr14_handler, 0x0e)
/* Reserved 0x0f */
MAKE_INTERRUPT        (isr16, isr0_handler,  0x10)
MAKE_INTERRUPT_ERRCODE(isr17, isr0_handler,  0x11)
MAKE_INTERRUPT        (isr18, isr0_handler,  0x12)
MAKE_INTERRUPT        (isr19, isr0_handler,  0x13)
MAKE_INTERRUPT        (isr20, isr0_handler,  0x14)
/* Reserved 0x15 to 0x1d */
MAKE_INTERRUPT_ERRCODE(isr30, isr0_handler,  0x1e)
/* Reserved 0x1f */

/* IRQ handlers */
MAKE_INTERRUPT        (irq0,  irq0_handler,  0x00)
MAKE_INTERRUPT        (irq1,  irq1_handler,  0x01)
MAKE_INTERRUPT        (irq2,  irq2_handler,  0x02)
MAKE_INTERRUPT        (irq3,  irq3_handler,  0x03)
MAKE_INTERRUPT        (irq4,  irq4_handler,  0x04)
MAKE_INTERRUPT        (irq5,  irq5_handler,  0x05)
MAKE_INTERRUPT        (irq6,  irq6_handler,  0x06)
MAKE_INTERRUPT        (irq7,  irq7_handler,  0x07)
MAKE_INTERRUPT        (irq8,  irq8_handler,  0x08)
MAKE_INTERRUPT        (irq9,  irq9_handler,  0x09)
MAKE_INTERRUPT        (irq10, irq10_handler,  0x0A)
MAKE_INTERRUPT        (irq11, irq11_handler,  0x0B)
MAKE_INTERRUPT        (irq12, irq12_handler,  0x0C)
MAKE_INTERRUPT        (irq13, irq13_handler,  0x0D)
MAKE_INTERRUPT        (irq14, irq14_handler,  0x0E)
MAKE_INTERRUPT        (irq15, irq15_handler,  0x0F)

void init_idt_entry(int num, unsigned int offset, unsigned short select, 
	unsigned short flags)
	{
		_idt_entries[num].base_low = (offset & 0xffff);
		_idt_entries[num].base_high =  (offset & 0xffff0000) >> 16;
		_idt_entries[num].always0 = 0;
		_idt_entries[num].flags = flags;
		_idt_entries[num].select = select;
		 return;
	}




///////////////////////////////////////
void idt_flush(struct idt *idtr)
{
	asm volatile("lidt %0" :: "m"(*idtr));
}

void init_pic()
{

	outb(0x20,0x11);
	outb(0xA0,0x11);

	outb(0x21, 0x20);
	outb(0xA1, 40);

	outb(0x21, 0x04);
	outb(0xA1, 0x02);

	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	
}


void init_idt()
{
	init_pic();
	Tidt.limit = 8 * 256;
	Tidt.base  = (int)&_idt_entries;


	memset(&_idt_entries, 0, 8*256);

	for(int i = 0; i < 256 ; i++){
		init_idt_entry(i,(int)&isr0,0x08, 0x8E); 
	}

	init_idt_entry(0,(int)&isr0,0x08, 0x8E);
	init_idt_entry(1,(int)&isr1,0x08, 0x8E);
	init_idt_entry(2,(int)&isr2,0x08, 0x8E);
	init_idt_entry(3,(int)&isr3,0x08, 0x8E);
	init_idt_entry(4,(int)&isr4,0x08, 0x8E);
	init_idt_entry(5,(int)&isr5,0x08, 0x8E);
	init_idt_entry(6,(int)&isr6,0x08, 0x8E);
	init_idt_entry(7,(int)&isr7,0x08, 0x8E);
	init_idt_entry(8,(int)&isr8,0x08, 0x8E);
	init_idt_entry(9,(int)&isr9,0x08, 0x8E);
	init_idt_entry(10,(int)&isr10,0x08, 0x8E);
	init_idt_entry(11,(int)&isr11,0x08, 0x8E);
	init_idt_entry(12,(int)&isr12,0x08, 0x8E);
	init_idt_entry(13,(int)&isr13,0x08, 0x8E);
	init_idt_entry(14,(int)&isr14,0x08, 0x8E);
	/* ISR15 is reserved */
	init_idt_entry(16,(int)&isr16,0x08, 0x8E);
	init_idt_entry(17,(int)&isr17,0x08, 0x8E);
	init_idt_entry(18,(int)&isr18,0x08, 0x8E);
	init_idt_entry(19,(int)&isr19,0x08, 0x8E);
	init_idt_entry(20,(int)&isr20,0x08, 0x8E);
	/* ISR21 to ISR2F are reserved */
	init_idt_entry(30,(int)&isr30,0x08, 0x8E);

	/* IRQ handlers */
	init_idt_entry(32,(int)&irq0,0x08, 0x8E);
	init_idt_entry(33,(int)&irq1,0x08, 0x8E);
	init_idt_entry(34,(int)&irq2,0x08, 0x8E);
	init_idt_entry(35,(int)&irq3,0x08, 0x8E);
	init_idt_entry(36,(int)&irq4,0x08, 0x8E);
	init_idt_entry(37,(int)&irq5,0x08, 0x8E);
	init_idt_entry(38,(int)&irq6,0x08, 0x8E);
	init_idt_entry(39,(int)&irq7,0x08, 0x8E);
	init_idt_entry(40,(int)&irq8,0x08, 0x8E);
	init_idt_entry(41,(int)&irq9,0x08, 0x8E);
	init_idt_entry(42,(int)&irq10,0x08, 0x8E);
	init_idt_entry(43,(int)&irq11,0x08, 0x8E);
	init_idt_entry(44,(int)&irq12,0x08, 0x8E);
	init_idt_entry(45,(int)&irq13,0x08, 0x8E);
	init_idt_entry(46,(int)&irq14,0x08, 0x8E);
	init_idt_entry(47,(int)&irq15,0x08, 0x8E);

	idt_flush(&Tidt);

	asm volatile("sti;");
	
	asm volatile ("int $0x4");
}