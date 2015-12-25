#include <string.h>

void* memset(void *dest, int ch, size_t count)
{
	unsigned char *buf = (unsigned char *)dest;

	for(size_t i = 0; i < count; i++)
	{
		buf[i] = (unsigned char)ch;
	}

	return dest;
}
