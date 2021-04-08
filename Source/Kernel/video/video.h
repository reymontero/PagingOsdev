#ifndef _VIDEO_H_
#define _VIDEO_H_

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define BITS_PER_PIXEL 32

struct vbe_mode_info_structure vbemode;


void putpixel(int x, int y, unsigned int color);

void drawLine(int x, int y, int x1, int y1, unsigned int color);

void drawVLine(int x, int y, int h, int color);

void drawHLine(int x, int y, int w, int color);

void drawRect(int x, int y, int h, int w, int color);

void fillRect(int x, int y, int h, int w, unsigned int color);

void drawTriangle(int x, int y, int x1, int y1, int x2, int y2, int color);

void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int c);

void drawCircle(int x, int y, int r, unsigned int c);

void fillCircle(int x, int y, int r, unsigned int c);

void drawChar(unsigned char c, int x, int y, int fgcolor, int bgcolor);

void drawCharToCursor(unsigned char c, int fgcolor, int bgcolor);

void drawString(const char* str, int x, int y, int fgcolor, int bgcolor);

void drawStringToCursor(const char* str, int fgcolor, int bgcolor);

 struct vbe_mode_info_structure {
	unsigned short attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	unsigned char window_a;			// deprecated
	unsigned char window_b;			// deprecated
	unsigned short granularity;		// deprecated; used while calculating bank numbers
	unsigned short window_size;
	unsigned short segment_a;
	unsigned short segment_b;
	unsigned int win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	unsigned short pitch;			// number of bytes per horizontal line
	unsigned short width;			// width in pixels
	unsigned short height;			// height in pixels
	unsigned char w_char;			// unused...
	unsigned char y_char;			// ...
	unsigned char planes;
	unsigned char bpp;			// bits per pixel in this mode
	unsigned char banks;			// deprecated; total number of banks in this mode
	unsigned char memory_model;
	unsigned char bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	unsigned char image_pages;
	unsigned char reserved0;
 
	unsigned char red_mask;
	unsigned char red_position;
	unsigned char green_mask;
	unsigned char green_position;
	unsigned char blue_mask;
	unsigned char blue_position;
	unsigned char reserved_mask;
	unsigned char reserved_position;
	unsigned char direct_color_attributes;
 
	unsigned int framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	unsigned int off_screen_mem_off;
	unsigned short off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	unsigned char reserved1[206];
} __attribute__ ((packed));

#endif