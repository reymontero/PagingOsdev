
#include "../video/video.h"
#include "../args/args.h"


char buffer[100];
void printk(const char* format, ...) 
{
	char * str = format;
	
	char *ite;
	
	va_list listPointer;

    va_start( listPointer, format );
	
	for (ite = format; *ite != '\0'; ite++) 
	{
		if (*ite == '%') 
		{
			ite++;
			
			switch(*ite)
			{
				case 'd':
					drawStringToCursor(itoa(va_arg(listPointer, int), buffer, 10), 0xffffff, 0x000000);
					break;
				case 's':
					drawStringToCursor(va_arg(listPointer, char *), 0xffffff, 0x000000);
					break;
				case 'x':
					drawStringToCursor(itoa(va_arg(listPointer, int), buffer, 16), 0xffffff, 0x000000);
					break;
				case '%':
					drawCharToCursor('%', 0xffffff, 0x000000);
					incrementCursor();
					break;
			}
		}
		else
		{
			drawCharToCursor(*ite, 0xffffff, 0x000000);
			incrementCursor();
		}
	}
	
	va_end(listPointer);
	
	
}


void panic(char* str)
{
	printk("PANIC: %s", str);
}


















