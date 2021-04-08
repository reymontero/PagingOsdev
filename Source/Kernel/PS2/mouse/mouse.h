#ifndef _MOUSE_H_
#define _MOUSE_H_

unsigned char readMouse();

unsigned char commandMouse(unsigned char command);

unsigned char initMouse();

unsigned int MouseX;
unsigned int MouseY;
#endif