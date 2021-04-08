#include "../io/io.h"
#include "ps2.h"

void controllerWait(unsigned char type) //unsigned char
{
  int _time_out=100000; //unsigned int
  if(type==0)
  {
    while(_time_out--) //Data
    {
      if((inb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

unsigned char getPS2ControllerStatus()
{
	controllerWait(1);
	outb(0x64, 0x20);
	controllerWait(0);
	return inb(0x60);
}

void setPS2ControllerStatus(unsigned char status)
{
	controllerWait(1);
	outb(0x64, 0x60);
	outb(0x60, status);
}

void disableSecondPS2Port()
{
	controllerWait(1);
	outb(0x64, 0xA7);
}

void enableSecondPS2Port()
{
	controllerWait(1);
	outb(0x64, 0xA8);
}

void disableFirstPS2Port()
{
	controllerWait(1);
	outb(0x64, 0xAD);
}

void enableFirstPS2Port()
{
	controllerWait(1);
	outb(0x64, 0xAE);
}

void commandPS2Controller(unsigned char command)
{
	controllerWait(1);
	outb(0x64, command);
}

void writeToFirstPS2Port(unsigned char byte)
{
	controllerWait(1);
	outb(0x60, byte);
}

void writeToSecondPS2Port(unsigned char byte)
{
	controllerWait(1);
	outb(0x64, 0xD4);
	controllerWait(1);
	outb(0x60, byte);
}

unsigned char readPS2DataPort()
{
	controllerWait(0);
	return inb(0x60);
}

int initPS2Controller()
{
	// Disable devices
	disableFirstPS2Port();
	disableSecondPS2Port();
	
	// flush output buffer
	inb(0x60);
	
	// set status
	unsigned char status = getPS2ControllerStatus();
	setPS2ControllerStatus(status & 0b10111100);
	
	// self test
	status = getPS2ControllerStatus();
	commandPS2Controller(0xAA);
	unsigned char response = readPS2DataPort();
	if(response != 0x55) return 1;
	setPS2ControllerStatus(status);
	
	// enable devices
	enableFirstPS2Port();
	enableSecondPS2Port();
	
	// enable interrupts
	status = getPS2ControllerStatus();
	setPS2ControllerStatus(status | 3);
	
	// reset devices
	writeToFirstPS2Port(0xFF);
	response = readPS2DataPort();
	if(response == 0xFC) return 2;
	writeToSecondPS2Port(0xFF);
	response = readPS2DataPort();
	if(response == 0xFC) return 2;
	
	return 0;
}






