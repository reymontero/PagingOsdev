#ifndef _PS2_H_
#define _PS2_H_

#include "./keyboard/keyboard.h"
#include "./mouse/mouse.h"

void controllerWait(unsigned char type);

unsigned char getPS2ControllerStatus();

void setPS2ControllerStatus(unsigned char status);

void disableSecondPS2Port();

void enableSecondPS2Port();

void disableFirstPS2Port();

void enableFirstPS2Port();

void commandPS2Controller(unsigned char command);

void writeToFirstPS2Port(unsigned char byte);

void writeToSecondPS2Port(unsigned char byte);

unsigned char readPS2DataPort();

int initPS2Controller();

#endif