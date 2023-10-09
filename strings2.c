#include "main.h"

/**
 * custom_strcpy - copies a string
 * @d: the destination str
 * @s: the source str
 *
 * Return: pointer to des
 */
char *custom_strcpy(char *d, char *s)
{
	int i = 0;

	if (d == s || s == 0)
		return (d);

	while (s[i])
	{
		d[i] = s[i];
		i++;
	}

	d[i] = 0;

	return (d);
}

/**
 * custom_putchar - implementaton of putchar()
 * @c: char to print
 *
 * Return: 1 (success)
 */
int custom_putchar(char c)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (c == RESET_BUF || i >= MAX_BUFFER_SIZE)
	{
		write(STDOUT_FILENO, buffer, i);
		i = 0;
	}

	if (c != RESET_BUF)
		buffer[i++] = c;

	return (1);
}

/**
 * custom_puts - implemetation of puts()
 * @s: input str
 */

void custom_puts(char *s)
{
	int i = 0;

	if (!s)
		return;

	while (s[i] != '\0')
	{
		custom_putchar(s[i]);
		i++;
	}
}

/**
 * custom_strdup - duplicates a string
 * @s: input string
 *
 * Return: ptr to duplicated str
 */
char *custom_strdup(const char *s)
{
	int len = 0;
	char *count;

	if (s == NULL)
		return (NULL);

	while (*s++)
		len++;

	count = malloc(sizeof(char) * (len + 1));
	if (!count)
		return (NULL);

	for (len++; len--;)
		count[len] = *--s;

	return (count);
}

/**
 * custom_putfd - writes the character c to given fd
 * @ch: char to print
 * @fd: filedescriptor
 *
 * Return: 1 (success)
 */

int custom_putfd(char ch, int fd)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (ch == RESET_BUF || i >= MAX_BUFFER_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (ch != RESET_BUF)
		buffer[i++] = ch;
	return (1);
}

