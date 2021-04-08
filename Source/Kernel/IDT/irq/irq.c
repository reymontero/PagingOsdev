
#include "irq.h"
#include "../../PS2/ps2.h"
#include "../../PS2/keyboard/keyboard.h"
#include "../../PS2/mouse/mouse.h"
#include "../../video/video.h" 
#include "../../string/string.h"

void default_irq_handler(interrupt_frame_t *frame)
{
        /* If IRQ # on slave PIC send EOI to slave */
        if (frame->int_num >= 8)
            outb(0xA0,0x20);

        /* Send EOI to master PIC */
        outb(0x20,0x20);
}

/* -------------------------- Programable Interval Timer ------------------------- */
void irq0_handler(interrupt_frame_t* frame)
{
	EnvironmentTick++;
	default_irq_handler(frame);
}

void Sleep(int ticks)
{
	int now = EnvironmentTick;

	while (EnvironmentTick != now + ticks);

	return;

}
void SetPITSpeed(int hz)
{
	int divisor = 1193180 / hz;       /* Calculate our divisor */
	outb(0x43, 0x36);             /* Set our command byte 0x36 */
	outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
	outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}
/*  ------------------------------------------------------------------------------ */


/* -------------------------- Keyboard Controller -------------------------------- */
unsigned char currentCharInScancode;
unsigned char currentCharInKeycode;
unsigned char currentCharInASCII;

int isE0 = 0;
int isE1 = 0;
int pause = 0;
int prntscrn = 0;	
int isKeyPressed = 0;
int ignore = 0;
int isShift = 0;
char kbd_buffer[100];
int bufferIterator = 0;
char buffer[8];

void irq1_handler(interrupt_frame_t* frame)
{
	
	currentCharInScancode = readKeyboard();
	
	if(ignore > 0)
	{
		ignore--;
		default_irq_handler(frame);
		return;
	}
	else if(currentCharInScancode == 0xE1 && pause == 0)
	{
		pause = 1;
		ignore = 5;
	}
	else if(currentCharInScancode == 0xE0)
	{
		isE0 = 1;
		default_irq_handler(frame);
		return;
	}
	else if(currentCharInScancode == 0xF0)
	{
		isKeyPressed = 2;
		default_irq_handler(frame);
		return;
	}
	else if(currentCharInScancode == 0x7C && isE0 == 1)
	{	
		prntscrn = 1;
		ignore = 2;
	}
	
	
	if(isKeyPressed == 0)
		isKeyPressed = 1;
	else if(isKeyPressed == 2)
		isKeyPressed = 0;
	
	currentCharInKeycode = ScancodeToKeyCode(currentCharInScancode, isE0, prntscrn, pause);
	if(isE0 == 1) isE0 = 0;
	if(pause == 1) pause = 0;
	if(prntscrn == 1) prntscrn = 0;
	
	//drawStringToCursor(itoa(isKeyPressed, buffer, 16), 0xffffff, 0x000000);
	
	KeyPressed[currentCharInKeycode] = isKeyPressed; 
	
	//drawStringToCursor(itoa(isKeyPressed, buffer, 16), 0xffffff, 0x000000);
	
	kbd_buffer[bufferIterator] = currentCharInKeycode;
	if(bufferIterator == 99) bufferIterator = 0;
	else bufferIterator++;
	
	/*
	if((KeyCodeToASCII(currentCharInKeycode, KeyPressed[LSHIFT] | KeyPressed[RSHIFT]) != 0) && isKeyPressed == 1) 
	{
		drawCharToCursor(KeyCodeToASCII(currentCharInKeycode, KeyPressed[LSHIFT] | KeyPressed[RSHIFT]), 0xffffff, 0x000000);
		incrementCursor();
	}*/
	default_irq_handler(frame);
}
/*  ------------------------------------------------------------------------------ */

 
void irq2_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq3_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq4_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq5_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq6_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq7_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq8_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq9_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq10_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq11_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}

// -------------------------------- Mouse Controller ------------------------

unsigned char mouse_cycle = 0;
signed char mouse_byte[3];    //signed char
signed char mouse_x = 0;         //signed char
signed char mouse_y = 0;         //signed char
signed char state = 0;
signed char d = 0;

int LeftButton = 0;
int MiddleButton = 0;
int RightButton = 0;

unsigned char buff[16];
void irq12_handler(interrupt_frame_t* frame)
{
	switch(mouse_cycle)
	{
		case 0:
			mouse_byte[0]=readMouse();
			mouse_cycle++;
			break;
		case 1:
			mouse_byte[1]=readMouse();
			mouse_cycle++;
			break;
		case 2:
			mouse_byte[2]=readMouse();
			
			
			state = mouse_byte[2];
			d = mouse_byte[0];
			mouse_x = d - ((state << 4) & 0x100);
			d = mouse_byte[1];		
			mouse_y = d - ((state << 3) & 0x100);
			
			MouseX = MouseX + mouse_x;
			MouseY = MouseY - mouse_y;
			
			putpixel(MouseX, MouseY, 0xffffff);
			
			if( (state & 0b00001100) == 0b00001100 ) MiddleButton = 1;
			else if( (state & 0b00001100) == 0b00001000 ) MiddleButton = 0;
			
			if( (state & 0b000010001) == 0b00001001 ) LeftButton = 1;
			else if( (state & 0b00001001) == 0b00001000 ) LeftButton = 0;
			
			if( (state & 0b00001010) == 0b00001010 ) RightButton = 1;
			else if( (state & 0b00001010) == 0b00001000 ) RightButton = 0;
			
			//drawStringToCursor(itoa(RightButton, buffer, 16), 0xffffff, 0x000000);
			//incrementCursor();
			mouse_cycle=0;
			break;
	}
	default_irq_handler(frame);
}
// --------------------------------------------------------------------------

void irq13_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq14_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}
void irq15_handler(interrupt_frame_t* frame)
{
	default_irq_handler(frame);
}