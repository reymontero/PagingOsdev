

#include "kmain.h"

int kmain(struct vbe_mode_info_structure *vbemodeinfo)
{
	
	vbemode = *vbemodeinfo;
	
	

	initDefaultFont();
	initCursor();
	drawStringToCursor("Successfully initialized Cursor and Font\n",0xffffff, 0x000000);
	
	init_idt();	
	drawStringToCursor("Successfully initialized Interrupts\n",0xffffff, 0x000000);
	
	SetPITSpeed(100);
	drawStringToCursor("Set PIT speed\n",0xffffff, 0x000000);	
	
	int succ = initPS2Controller();
	if(succ == 0) drawStringToCursor("Successfully initialized PS2 Controller\n",0xffffff, 0x000000);
	else drawStringToCursor("A problem occured while initializing PS2 Controller\n",0xffffff, 0x000000);

	unsigned char s = initKeyboard();
	if(s == 0xFA) drawStringToCursor("Successfully initialized Keyboard Controller\n",0xffffff, 0x000000);
	else drawStringToCursor("A problem occured while initializing Keyboard Controller\n",0xffffff, 0x000000);
	
	s = initMouse();
	if(s == 0xFA) drawStringToCursor("Successfully initialized Mouse Controller\n",0xffffff, 0x000000);
	else drawStringToCursor("A problem occured while initializing Mouse Controller\n",0xffffff, 0x000000);
	
	initPaging();
	
	printk("Hello %d", 15) ;
	
	
	while(1);
	
	return 0;
}


