#include <string.h>

size_t strlen(const char *str)
{
	size_t result = 0;

	while(str[result] != 0)
	{
		result++;
	}

	return result;
}
