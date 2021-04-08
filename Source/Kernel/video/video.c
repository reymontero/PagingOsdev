#include "video.h"
#include "font.h"
#include "cursor.h"
#include "../math/math.h"
#include "../string/string.h"

void putpixel(int x, int y, unsigned int color)
{
	unsigned char *screen = vbemode.framebuffer;
	unsigned int where = x * 4 + y * 1920*4;
	
	screen[where+2] = (color >> 16) & 255;
	screen[where+1] = (color >> 8) & 255;
	screen[where] = color & 255;
}



void drawLine(int x, int y, int x1, int y1, unsigned int color)
{
    int steep = abs(y1 - y) > abs(x1 - x);
    if (steep) {
        int temp = x;
        x = y;
        y = temp;
 
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
 
    if (x > x1) {
        int temp = x;
        x = x1;
        x1 = temp;
 
        temp = y;
        y = y1;
        y1 = temp;
    }
 
    int dx, dy;
    dx = x1 - x;
    dy = abs(y1 - y);
 
    int err = dx / 2;
    int ystep;
 
    if (y < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }
 
    for (; x <= x1; x++) {
        if (steep) {
            putpixel(y, x, color);
        } else {
            putpixel(x, y, color);
        }
        err -= dy;
        if (err < 0) {
            y+= ystep;
            err += dx;
        }
    }
}
void drawVLine(int x, int y, int h, int color)
{
	unsigned char *screen = vbemode.framebuffer;
	unsigned int where = x * 4 + y * 1920 * 4;	
	
	for(int i = 0; i < h; i++)
	{
		screen[where+(i*4* 1920)+2] = (color >> 16) & 255;
		screen[where+(i*4* 1920)+1] = (color >> 8) & 255;
		screen[where+(i*4* 1920)] = color & 255;
	}
}

void drawHLine(int x, int y, int w, int color)
{
	unsigned char *screen = vbemode.framebuffer;
	unsigned int where = x * 4 + y * 1920 * 4;	
	
	for(int i = 0; i < w; i++)
	{
		screen[where+(i*4)+2] = (color >> 16) & 255;
		screen[where+(i*4)+1] = (color >> 8) & 255;
		screen[where+(i*4)] = color & 255;
	}
}

void drawRect(int x, int y, int h, int w, int color)
{
	drawHLine(x, y, w, color);
	drawVLine(x, y, h, color);
	drawHLine(x, y+h, w, color);
	drawVLine(x+w, y, h, color);
}	

void fillRect(int x, int y, int h, int w, unsigned int color)
{
	unsigned char *screen = vbemode.framebuffer;
	unsigned int where = x*4 + y * 1920 *4;
	
	int i = 0, j = 0;
	for(i = 0; i < h; i++)
	{	
		for(j = 0; j < w; j++ )
		{
			screen[where+(j*4)+2] = (color >> 16) & 255;
			screen[where+(j*4)+1] = (color >> 8) & 255;
			screen[where+(j*4)] = color & 255;
		}
		where += 1920*4;
	}
}

void drawTriangle(int x, int y, int x1, int y1, int x2, int y2, int color)
{
	drawLine(x,y,x1,y1,color);
	drawLine(x1,y1,x2,y2,color);
	drawLine(x,y,x2,y2,color);
}

void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int c)
{
    int a, b, y, last;
 
    //Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        int temp = y0;
        y0 = y1;
        y1 = temp;
 
        temp = x0;
        x0 = x1;
        x1 = temp;
    }
    if (y1 > y2) {
        int temp = y1;
        x1 = y2;
        y2 = temp;
 
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y0 > y1) {
        int temp = y0;
        y0 = y1;
        y1 = temp;
 
        temp = x0;
        x0 = x1;
        x1 = temp;
    }
 
    //Handle awkward all-on-same-line case as its own thing
    if(y0 == y2) {
        a = b = x0;
        if(x1 < a)
            a = x1;
        else if(x1 > b)
            b = x1;
        if(x2 < a)
            a = x2;
        else if(x2 > b)
            b = x2;
 
        drawHLine(a, y0, b - a + 1, c);
 
        return;
    }
 
    int dx01 = x1 - x0;
    int dy01 = y1 - y0;
    int dx02 = x2 - x0;
    int dy02 = y2 - y0;
    int dx12 = x2 - x1;
    int dy12 = y2 - y1;
    int sa = 0;
    int sb = 0;
 
    //For upper part of triangle, find scanline crossings for segments
    //0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    //is included here (and second loop will be skipped, avoiding a /0
    //error there), otherwise scanline y1 is skipped here and handled
    //in the second loop...which also avoids a /0 error here if y0=y1
    //(flat-topped triangle).
    if(y1 == y2)
        last = y1;      //Include y1 scanline
    else
        last = y1 - 1;  //Skip it
 
    for(y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
 
        if(a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        drawHLine(a, y, b - a + 1, c);
    }
 
    //For lower part of triangle, find scanline crossings for segments
    //0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
 
        if(a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        drawHLine(a, y, b - a + 1, c);
    }
}

void drawCircle(int x, int y, int r, unsigned int c)
{
	int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int i = 0;
    int j = r;
 
    putpixel(x, y + r, c);
    putpixel(x, y - r, c);
    putpixel(x + r, y, c);
    putpixel(x - r, y, c);
 
    while(i < j) {
        if(f >= 0) {
            j--;
            ddF_y += 2;
            f += ddF_y;
        }
        i++;
        ddF_x += 2;
        f += ddF_x;
        putpixel(x + i, y + j, c);
        putpixel(x - i, y + j, c);
        putpixel(x + i, y - j, c);
        putpixel(x - i, y - j, c);
        putpixel(x + j, y + i, c);
        putpixel(x - j, y + i, c);
        putpixel(x + j, y - i, c);
        putpixel(x - j, y - i, c);
    }
}

void fillCircle(int x, int y, int r, unsigned int c)
{
	int corner = 3, delta=0;
	drawVLine(x, y - r, 2 * r + 1, c);
	
	int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int i = 0;
    int j = r;
 
    while (i < j) {
        if (f >= 0) {
            j--;
            ddF_y += 2;
            f += ddF_y;
        }
        i++;
        ddF_x += 2;
        f += ddF_x;
 
        if (corner & 0x1) {
            drawVLine(x + i, y - j, 2 * j + 1 + delta, c);
            drawVLine(x + j, y - i, 2 * i + 1 + delta, c);
        }
        if (corner & 0x2) {
            drawVLine(x - i, y - j, 2 * j + 1 + delta, c);
            drawVLine(x - j, y - i, 2 * i + 1 + delta, c);
        }
    }
}

unsigned char *font = Default_T_font;
void drawChar(unsigned char c, int x, int y, int fgcolor, int bgcolor)
{
	int cx,cy;
	int mask[8]={128,64,32,16,8,4,2,1};
	unsigned char *gylph=font+(int)c*16;
 
	for(cy=0;cy<16;cy++){
		for(cx=0;cx<8;cx++){
			putpixel(x+cx,y+cy-12, gylph[cy]&mask[cx]?fgcolor:bgcolor);
		}
	}
}

void drawCharToCursor(unsigned char c, int fgcolor, int bgcolor)
{
	int x = getCursorX();
	int y = getCursorY();
	int cx,cy;
	int mask[8]={128,64,32,16,8,4,2,1};
	unsigned char *gylph=font+(int)c*16;
 
	for(cy=0;cy<16;cy++){
		for(cx=0;cx<8;cx++){
			putpixel(x+cx,y+cy-12, gylph[cy]&mask[cx]?fgcolor:bgcolor);
		}
	}
	//incrementCursor();
}






void drawString(const char* str, int x, int y, int fgcolor, int bgcolor )
{
	int cursorx = 0;
	int cursory = 0;
	
    for(int i = 0; i < strlen(str); i++)
	{
		
		
		if(str[i] == '\n' && cursory <= 1080) {cursorx = 0; cursory += Default_Attribute.cheight; continue;}
		
		drawChar(str[i], x+cursorx, y+cursory, fgcolor, bgcolor);
		
		cursorx += Default_Attribute.cwidth;
		
		if(cursorx >= SCREEN_WIDTH) {cursorx = 0; cursory += Default_Attribute.cheight;}
		

	}
	
}

void drawStringToCursor(const char* str, int fgcolor, int bgcolor )
{
	int x = getCursorX();
	int y = getCursorY();
	int cursorx = 0;
	int cursory = 0;
	
    for(int i = 0; i < strlen(str); i++)
	{
		
		
		if(str[i] == '\n' && cursory <= 1080) {nextLine(); continue;}
		
		drawCharToCursor(str[i], fgcolor, bgcolor);
		
		incrementCursor();
		
		

	}
	
}







