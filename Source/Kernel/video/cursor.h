

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "font.h"
#include "video.h"

struct Cursor
{
	unsigned int x;
	unsigned int y;
} defaultCursor;

void initCursor(int x, int y)
{
	defaultCursor.x = 0;
	defaultCursor.y = Default_Attribute.cheight;
}

void setCursor(int x, int y)
{
	defaultCursor.x = x;
	defaultCursor.y = y;
}

struct Cursor getCursor()
{
	return defaultCursor;
}

int getCursorX()
{
	return defaultCursor.x;
}

int getCursorY()
{
	return defaultCursor.y;
}

void incrementCursor()
{
	int currentX = getCursorX();
	int currentY = getCursorY();

	if(currentX > SCREEN_WIDTH-Default_Attribute.cwidth && currentY <= SCREEN_HEIGHT) setCursor(0, currentY+Default_Attribute.cheight);
	else setCursor(currentX+Default_Attribute.cwidth, currentY);
}

void nextLine()
{
	int currentY = getCursorY();

	if(currentY <= SCREEN_HEIGHT) setCursor(0, currentY+Default_Attribute.cheight);
}

#endif