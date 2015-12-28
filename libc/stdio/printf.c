#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void print(const char *data, size_t length)
{
	for(size_t i = 0; i < length; i++)
	{
		putchar((int)((const unsigned char *) data)[i]);
	}
}

static void number(int i, char s[])
{
	char *p = s;

	if(i < 0)
	{
		*p++ = '-';
		i = -i;
	}

	int temp = i;

	do
	{
		p++;
		temp /= 10;
	} while(temp != 0);

	*p = '\0';

	do
	{
		*--p = (i % 10) + 48;
		i /= 10;
	} while(i != 0);
}

int printf(const char *restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;
	size_t amount;

	while(*format != '\0')
	{
		if(*format != '%')
		{
			amount = 1;

			while(format[amount] != '\0' && format[amount] != '%')
			{
				amount++;
			}

			print(format, amount);
			format += amount;
			written += amount;
		}
		else
		{
			format++;

			if(*format == 'c')
			{
				format++;
				char c = (char)va_arg(parameters, int);
				print(&c, sizeof(c));
				written++;
			}
			else if(*format == 'd')
			{
				format++;
				char s[11];
				number(va_arg(parameters, int), s);
				size_t length = strlen(s);
				print(s, length);
				written += length;
			}
			else if(*format == 's')
			{
				format++;
				const char *s = va_arg(parameters, const char *);
				size_t length = strlen(s);
				print(s, length);
				written += length;
			}
		}
	}

	va_end(parameters);

	return written;
}
