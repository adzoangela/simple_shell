#include "main.h"

/**
 **custom_strncpy - copies a string
 *@d: destination string
 *@s: src string
 *@bytes: bytes copied
 *
 *Return: concatenated string
 */
char *custom_strncpy(char *d, char *s, int bytes)
{
	int i, j;
	char *str = d;

	i = 0;
	while (s[i] != '\0' && i < bytes - 1)
	{
		d[i] = s[i];
		i++;
	}

	if (i < bytes)
	{
		j = i;

		while (j < bytes)
		{
			d[j] = '\0';
			j++;
		}
	}

	return (str);
}

/**
 **custom_strchr - finds a char in a given string
 *@str: the string to
 *@c: the character to look for
 *Return: ptr to str
 */

char *custom_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}

/**
 **custom_strncat - concats two strings
 *@d: destination
 *@s: source
 *@bytes: no of  bytes
 *
 *Return: ptr to concatenated string
 */

char *custom_strncat(char *d, char *s, int bytes)
{
	int i, j;
	char *str = d;

	i = 0;
	j = 0;

	while (d[i] != '\0')
		i++;

	while (s[j] != '\0' && j < bytes)
	{
		d[i] = s[j];
		i++;
		j++;
	}

	if (j < bytes)
		d[i] = '\0';

	return (str);
}

/**
 * check_delim - check for delim
 * @c: the char
 * @delim: delim string
 *
 * Return: 1 (true), 0 (false)
 */

int check_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);

	return (0);
}

