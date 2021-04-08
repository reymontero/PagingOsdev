

#ifndef _IRQ_H_
#define _IRQ_H_

#include "../IDT.h"



void default_irq_handler(interrupt_frame_t *frame);

void irq0_handler(interrupt_frame_t* frame);

void Sleep(int ticks);

void SetPITSpeed(int hz);


#endif
