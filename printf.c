#include "main.h"
#include "stdlib.h"
#include "stdarg.h"

/**
 * _printf - cudtom printf fn
 *
 * @param format Initial string
 * @param ...
 * Return: string with characters and format sprcifiers expanded
 */

int _printf(const char *format, ...)
{
	int len = 0, i = 0, j = 0, total_len = 0;
	va_list list;
	char* (*f)(va_list);
	char *str, *buffer;

	if (format == NULL)
		return (-1);

	buffer = create_buffer();
	if (buffer == NULL)
		return (-1);

	va_start(list, format);

	while (format[i] != '\0') /* check if text format is null terminator*/
	{
		if (format[i] != '%') /* copy text format into buffer until '%' */
		{
			len = check_buffer_overflow(buffer, len);
			buffer[len++] = format[i++];
			total_len++;
		}
		else /* Handle the % sign by checling its next format specifier*/
		{
			i++;
			if (format[i] == '\0') /* handle single ending % */
			{
				va_end(list);
				free(buffer);
				return (-1);
			}
			if (format[i] == '%') /* handle double %'s */
			{
				len = check_buffer_overflow(buffer, len);
				buffer[len++] = format[i];
				total_len++;
			}
			else
			{
				f = get_func(format[i]); /* grab function */
				if (f == NULL)  /* handle fake id */
				{
					len = check_buffer_overflow(buffer, len);
					buffer[len++] = '%';
					total_len++;
					buffer[len++] = format[i];
					total_len++;
				}
				else /* return string, copy to buffer */
				{
					str = f(list);
					if (str == NULL)
					{
						va_end(list);
						free(buffer);
						return (-1);
					}
					if (format[i] == 'c' && str[0] == '\0')
					{
						len = check_buffer_overflow(buffer, len);
						buffer[len++] = '\0';
						total_len++;
					}
					j = 0;
					while (str[j] != '\0')
					{
						len = check_buffer_overflow(buffer, len);
						buffer[len++] = str[j];
						total_len++;
						j++;
					}
					free(str);
				}
			} i++;
		}
	}
	write_buffer(buffer, len, list);
	return (total_len);
}
