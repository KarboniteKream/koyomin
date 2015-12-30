#include <string.h>

void *memmove(void *dest, const void *src, size_t count)
{
	uint8_t *d = (uint8_t *)dest;
	const uint8_t *s = (const uint8_t *)src;

	if(d < s)
	{
		for(size_t i = 0; i < count; i++)
		{
			d[i] = s[i];
		}
	}
	else
	{
		for(size_t i = count; i != 0; i--)
		{
			d[i - 1] = s[i - 1];
		}
	}

	return dest;
}
