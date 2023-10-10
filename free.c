#include "main.h"

/**
 * free3 - free ptr
 * @ptr: pointer to free
 * Return: 1 (success), 0 otherwise
 */
int free3(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);

		*ptr = NULL;

		return (1);
	}

	return (0);
}

/**
 * free2 - frees a string of strings
 * @ptr: string of strings
 */
void free2(char **ptr)
{
	char **all = ptr;

	if (ptr == NULL)
		return;

	while (*ptr)
		free(*ptr++);

	free(all);
}

/**
 * custom_realloc - re-allocate block of memory
 * @ptr: ptr to prev allocated mem
 * @old_size: size of prev block
 * @new_size: size of new block
 * Return: pointer allocated.
 */

void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pp;

	if (ptr == NULL)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	pp = malloc(new_size);
	if (!pp)
		return (NULL);

	old_size = (old_size < new_size) ? (old_size) : (new_size);

	while (old_size--)
		pp[old_size] = ((char *)ptr)[old_size];

	free(ptr);

	return (pp);
}

