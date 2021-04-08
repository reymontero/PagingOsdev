
#include "../video/video.h"
#include "../string/string.h"
#include "../IO/io.h"
#include "./isr/isr.h"
#include "./irq/irq.h"


#ifndef _IDT_H_
#define _IDT_H_




#define IDTBASE    0x00000000
#define IDTSIZE 0xFF

int EnvironmentTick;

struct idt
{
	short limit;
	unsigned int base;
}__attribute__ ((packed));

struct idt_entry
{
	short base_low;
    short select;
    char always0;
    char flags;
    short base_high;
}__attribute__ ((packed));

typedef struct {
    /* Pushed explicitly in our common stub code */
    unsigned int gs, fs, es, ds;
    /* Pushed in our stub code by pushad instruction */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_num;         /* Interrupt number */
    unsigned int err_code;        /* Error Code */
    unsigned int eip, cs, eflags; /* Pushed by processor */
    unsigned int usersp, userss;  /* Pushed by procssor in some circumstances */
} interrupt_frame_t;

struct idt Tidt;
struct idt_entry _idt_entries[256];

void init_idt_entry(int num, unsigned int offset, unsigned short select, 
        unsigned short flags);

void idt_flush(struct idt *idtr);

void init_pic();

void init_idt();

#endif