#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static size_t convert_number(char *destination, uintmax_t value, uint8_t base, const char *digits)
{
	size_t result = 1;

	uintmax_t copy = value;
	while(base <= copy)
	{
		copy /= base;
		result++;
	}
	for(size_t i = result; i != 0; i--)
	{
		destination[i - 1] = digits[value % base];
		value /= base;
	}

	return result;
}

static void print(const char *data, size_t length)
{
	for(size_t i = 0; i < length; i++)
		putchar((int)((const unsigned char *)data)[i]);
}

int printf(const char *restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;
	size_t amount;

	while(*format != '\0')
	{
		if(*format != '%' || (*format == '%' && *(++format) == '%'))
		{
			amount = 1;

			while(format[amount] != '\0' && format[amount] != '%')
				amount++;

			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}

		enum length
		{
			LENGTH_SHORT_SHORT,
			LENGTH_SHORT,
			LENGTH_DEFAULT,
			LENGTH_LONG,
			LENGTH_LONG_LONG,
			LENGTH_INTMAX_T,
			LENGTH_SIZE_T
		};

		struct length_modifier
		{
			const char *name;
			enum length length;
		};

		struct length_modifier length_modifiers[] =
		{
			{ "hh", LENGTH_SHORT_SHORT },
			{ "h", LENGTH_SHORT },
			{ "", LENGTH_DEFAULT },
			{ "l", LENGTH_LONG },
			{ "ll", LENGTH_LONG_LONG },
			{ "j", LENGTH_INTMAX_T },
			{ "z", LENGTH_SIZE_T }
		};

		enum length length = LENGTH_DEFAULT;
		size_t type_length = 0;

		for(size_t i = 0; i < sizeof(length_modifiers) / sizeof(length_modifiers[0]); i++)
		{
			size_t name_length = strlen(length_modifiers[i].name);

			if(name_length < type_length)
				continue;

			bool different = false;
			for(size_t n = 0; n < name_length; n++)
			{
				if(format[n] != length_modifiers[i].name[n])
				{
					different = true;
					break;
				}
			}

			if(different == true)
				continue;

			length = length_modifiers[i].length;
			type_length = name_length;
		}

		format += type_length;

		if(*format == 'd' || *format == 'i' || *format == 'o' || *format == 'u' || *format == 'x' || *format == 'X' || *format == 'p')
		{
			char conversion = *format++;
			bool negative_value = false;
			uintmax_t value;

			if(conversion == 'd' || conversion == 'i')
			{
				intmax_t signed_value;
				if(length == LENGTH_SHORT_SHORT)
					signed_value = va_arg(parameters, int);
				else if(length == LENGTH_SHORT)
					signed_value = va_arg(parameters, int);
				else if(length == LENGTH_DEFAULT)
					signed_value = va_arg(parameters, int);
				else if(length == LENGTH_LONG)
					signed_value = va_arg(parameters, long);
				else if(length == LENGTH_LONG_LONG)
					signed_value = va_arg(parameters, long long);
				else if(length == LENGTH_INTMAX_T)
					signed_value = va_arg(parameters, intmax_t);
				// else if(length == LENGTH_SIZE_T)
				// 	signed_value = va_arg(parameters, ssize_t);
				else
					return -1;
				value = (negative_value = signed_value < 0) ? -(uintmax_t)signed_value : (uintmax_t)signed_value;
			}
			else
			{
				if(length == LENGTH_SHORT_SHORT)
					value = va_arg(parameters, unsigned int);
				else if(length == LENGTH_SHORT)
					value = va_arg(parameters, unsigned int);
				else if(length == LENGTH_DEFAULT)
					value = va_arg(parameters, unsigned int);
				else if(length == LENGTH_LONG)
					value = va_arg(parameters, unsigned long);
				else if(length == LENGTH_LONG_LONG)
					value = va_arg(parameters, unsigned long long);
				else if(length == LENGTH_INTMAX_T)
					value = va_arg(parameters, uintmax_t);
				else if(length == LENGTH_SIZE_T)
					value = va_arg(parameters, size_t);
				else
					return -1;
			}

			if(negative_value == true)
				putchar('-');

			char output[sizeof(uintmax_t) * 3];
			uint8_t base = (conversion == 'x' || conversion == 'X') ? 16 : conversion == 'o' ? 8 : 10;
			const char *digits = conversion == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
			size_t length = convert_number(output, value, base, digits);
			print(output, length);
			written += length;
		}
		else if(*format == 'c')
		{
			format++;
			char c = (char)va_arg(parameters, int);
			print(&c, sizeof(c));
			written++;
		}
		else if(*format == 's')
		{
			format++;
			const char *s = va_arg(parameters, const char *);
			size_t length = strlen(s);
			print(s, length);
			written += length;
		}
		else
		{
			// TODO: Error (eg. trailing %).
			return -1;
		}
	}

	va_end(parameters);

	return written;
}
