#ifndef _MEMORY_H_
#define _MEMORY_H_

 
void memcpy(unsigned char *dest, const unsigned char *src, unsigned char len);

void memset(unsigned char *dest, unsigned char val, unsigned char len);

void memmove(unsigned char *dest, unsigned char *src, unsigned char len);

int memcmp(const unsigned char *src1, const unsigned char *src2, unsigned int len);

#endif