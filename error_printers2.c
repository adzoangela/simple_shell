#include "main.h"

/**
 * conv_num - a clone of itoa
 * @num: number
 * @b: base
 * @f: argument flags
 * Return: string
 */
char *conv_num(long int num, int b, int f)
{
	char *arr;
	char buf[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(f & CUSTOM_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}

	arr = (f & CUSTOM_LOWERCASE) ? ("0123456789abcdef") : ("0123456789ABCDEF");

	ptr = &buf[49];

	*ptr = '\0';

	do	{
		*--ptr = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * error_atoi - converts a str to an int
 * @str: the string to be converted
 *
 * Return: result
 */
int error_atoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;

	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');

			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (res);
}

/**
 * error_print - print error message
 * @information: the parameter & return info struct
 * @str: string containing specified error type
 */
void error_print(info_struct *information, char *str)
{
	error_puts(information->fname);
	error_puts(": ");
	_print(information->line_count, STDERR_FILENO);
	error_puts(": ");
	error_puts(information->argv[0]);
	error_puts(": ");
	error_puts(str);
}

/**
 * _print - function prints a decimal (integer) number (base 10)
 * @msg: the input
 * @filedesc: filedescriptor
 * Return: num of char printed
 */

int _print(int msg, int filedesc)
{
	int (*__putchar)(char) = custom_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (filedesc == STDERR_FILENO)
		__putchar = error_putchar;

	if (msg < 0)
	{
		_abs_ = -msg;
		__putchar('-');
		count++;
	}

	else
		_abs_ = msg;
	current = _abs_;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * hush_comments - handle comments
 * @buffer: adr of the str to modify
 * Return: 0;
 */

void hush_comments(char *buffer)
{
	int i;

	/*handle comment*/
	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}

