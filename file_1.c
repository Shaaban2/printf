#include "main.h"

void print_output(char output_buffer[], int *output_index);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed characters.
 */
int _printf(const char *format, ...)
{
	int j, showcase = 0, printed_characters = 0;
	int flags, width, precision, size, output_index = 0;
	va_list list;
	char output_buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (j = 0; format && format[j] != '\0'; j++)
	{
		if (format[j] != '%')
		{
			output_buffer[output_index++] = format[j];
			if (output_index == BUFF_SIZE)
				print_output(output_buffer, &output_index);
			/* write(1, &format[j], 1);*/
			printed_characters++;
		}
		else
		{
			print_output(output_buffer, &output_index);
			flags = get_flags(format, &j);
			width = get_width(format, &j, list);
			precision = get_precision(format, &j, list);
			size = get_size(format, &j);
			++j;
			showcase = handle_print(format, &j, list, output_buffer,
				flags, width, precision, size);
			if (showcase == -1)
				return (-1);
			printed_characters += showcase;
		}
	}

	print_output(output_buffer, &output_index);

	va_end(list);

	return (printed_characters);
}

/**
 * print_output - Prints the contents of the output_buffer if it exist
 * @output_buffer: Array of chars
 * @output_index: Index at which to add next char, represents the length.
 */
void print_output(char output_buffer[], int *output_index)
{
	if (*output_index > 0)
		write(1, &output_buffer[0], *output_index);

	*output_index = 0;
}

