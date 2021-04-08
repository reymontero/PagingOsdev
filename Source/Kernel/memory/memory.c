#include "./memory.h"
 
void memcpy(unsigned char *dest, const unsigned char *src, unsigned char len)
{
	const unsigned char *sp = (const unsigned char *) src;
	unsigned char *dp = (unsigned char *) dest;
	while (len--)
	{
		*dp++ = *sp++;
	}
}

void memset(unsigned char *dest, unsigned char val, unsigned char len)
{
	unsigned char *temp = (unsigned char *) dest;
	while (len--)
	{
		*temp++ = val;
	}
}

void memmove(unsigned char *dest, unsigned char *src, unsigned char len)
{
	unsigned char *sp = (unsigned char *) src;
	unsigned char *dp = (unsigned char *) dest;
	if (dp < sp)
	{
		while (len--)
		{
			*dp++ = *sp++;
		}
	}
	else
	{
		unsigned char *lasts = sp + (len - 1);
		unsigned char *lastd = dp + (len - 1);
		while (len--)
		{
			*lastd-- = *lasts--;
		}
	}
}

int memcmp(const unsigned char *src1, const unsigned char *src2, unsigned int len)
{
	const unsigned char *s1 = (const unsigned char *) src1;
	const unsigned char *s2 = (const unsigned char *) src2;
	while (len--)
	{
		if (*s1++ != *s2++)
		{
			return s1[-1] < s2[-1] ? -1 : 1;
		}
	}
	return 0;
}