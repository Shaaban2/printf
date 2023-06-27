#include "main.h"
/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @types: List of arguments
 * @output_buffer: Output buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_unsigned(va_list types, char output_buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		output_buffer[j--] = '0';

	output_buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		output_buffer[j--] = (number % 10) + '0';
		number /= 10;
	}

	j++;

	return (write_unsgnd(0, j, output_buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: List of arguments
 * @output_buffer: Output buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list types, char output_buffer[],
	int flags, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		output_buffer[j--] = '0';

	output_buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		output_buffer[j--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & F_HASH && init_number != 0)
		output_buffer[j--] = '0';

	j++;

	return (write_unsgnd(0, j, output_buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @output_buffer: Output buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list types, char output_buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", output_buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List of arguments
 * @output_buffer: Output buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa_upper(va_list types, char output_buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", output_buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper case
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @output_buffer: Output buffer array to handle print
 * @flags: Calculates active flags
 * @flag_ch: Flag character
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char output_buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		output_buffer[j--] = '0';

	output_buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		output_buffer[j--] = map_to[number % 16];
		number /= 16;
	}

	if (flags & F_HASH && init_number != 0)
	{
		output_buffer[j--] = flag_ch;
		output_buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, output_buffer, flags, width, precision, size));
}

