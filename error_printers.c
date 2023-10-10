#include "main.h"

/**
 * error_puts - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void error_puts(char *string)
{
	int n;

	n = 0;
	if (string == NULL)
		return;
	while (string[n] != '\0')
	{
		custom_putchar(string[n]);
		n++;
	}
}

/**
 * error_putchar - writes the character c to stderr
 * @charac: char to print
 *
 * Return: 1 (Success)
 */
int error_putchar(char charac)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (charac == RESET_BUF || i >= MAX_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}

	if (charac != RESET_BUF)
		buffer[i++] = charac;

	return (1);
}

/**
 * error_putsfd - prints input str
 * @str: the input str
 * @filedesc: the filedescriptorto write to
 * Return: the number of chars put
 */

int error_putsfd(char *str, int filedesc)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (*str)
	{
		i += write(filedesc, str, 1);
		str++;
	}

	return (i);
}
