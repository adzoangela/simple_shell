#include "main.h"

/**
 * mem_init - fills memory with byte
 * @st: the pointer
 * @ba: the byte
 * @n: the amount of bytes
 * Return: st
 */
char *mem_init(char *st, char ba, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		st[a] = ba;
	return (st);
}

/**
 * custom_start - checks if n starts with h
 * @h: string
 * @n: the other string
 * Return: address
 */
char *custom_start(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}
