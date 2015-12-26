#include <stdbool.h>
#include <stdlib.h>

void exit(int status)
{
	while(true)
	{
		(void)status;
	}

	__builtin_unreachable();
}
