#include "isr.h"

void isr0_handler(interrupt_frame_t *frame)
{
	panic("Divide by zero");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr1_handler(interrupt_frame_t *frame)
{
	panic("Debug");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr2_handler(interrupt_frame_t *frame)
{
	panic("NMI");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr3_handler(interrupt_frame_t *frame)
{
	panic("Breakpoint");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr4_handler(interrupt_frame_t *frame)
{
	panic("Overflow");
   //fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr5_handler(interrupt_frame_t *frame)
{
	panic("Bound range exceeded");
   //fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr6_handler(interrupt_frame_t *frame)
{
	panic("Invalid Opcode");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr7_handler(interrupt_frame_t *frame)
{
	panic("Device Not Available");
   //fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr8_handler(interrupt_frame_t *frame)
{
	panic("Double Fault");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr9_handler(interrupt_frame_t *frame)
{
	panic("COPRO SEGMENT OVERRUN");
   //fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr10_handler(interrupt_frame_t *frame)
{
	panic("Invalid TSS");
   //fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr11_handler(interrupt_frame_t *frame)
{
	panic("Segment Not present");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr12_handler(interrupt_frame_t *frame)
{
	panic("Stack Segment Fault");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr13_handler(interrupt_frame_t *frame)
{
	panic("General Protection Fault");
	//fillRect(0, 0, 1080, 1920, 0xff0000);
}
void isr14_handler(interrupt_frame_t *frame)
{
	//panic("Page Fault");
	
	unsigned int err = frame->err_code;
	
	//asm(".intel_syntax noprefix");
	asm("mov %0, %%eax "::"r"(err));
	
	
	
	
	
	
	
	while(1);
   //fillRect(0, 0, 1080, 1920, 0xff0000);
}