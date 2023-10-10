#include "main.h"

/**
 * custom_strtow - token string. ignore repeat delimiters
 * @str: input string
 * @delim: delimeters
 *
 * Return: ptr  to strings
 */

char **custom_strtow(char *str, char *delim)
{
	int i, j, k, m, word_count = 0;
	char **sec;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (delim == NULL)
		delim = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!check_delim(str[i], delim) && (check_delim(str[i + 1], delim)
				|| !str[i + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	sec = malloc((1 + word_count) * sizeof(char *));
	if (!sec)
		return (NULL);
	for (i = 0, j = 0; j < word_count; j++)
	{
		while (check_delim(str[i], delim))
			i++;
		k = 0;
		while (!check_delim(str[i + k], delim) && str[i + k])
			k++;
		sec[j] = malloc((k + 1) * sizeof(char));
		if (!sec[j])
		{
			for (k = 0; k < j; k++)
				free(sec[k]);
			free(sec);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sec[j][m] = str[i++];
		sec[j][m] = 0;
	}
	sec[j] = NULL;
	return (sec);
}

/**
 * custom_strtow2 - tokenize string
 * @str: input string
 * @delim: delimeter
 * Return: pointer string array, otherwise NULL
 */
char **custom_strtow2(char *str, char delim)
{
	int i, j, k, m, word_count = 0;
	char **sec;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
				    (str[i] != delim && !str[i + 1])
						|| str[i + 1] == delim)
			word_count++;
	if (word_count == 0)
		return (NULL);
	sec = malloc((1 + word_count) * sizeof(char *));
	if (!sec)
		return (NULL);

	for (i = 0, j = 0; j < word_count; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		sec[j] = malloc((k + 1) * sizeof(char));
		if (!sec[j])
		{
			for (k = 0; k < j; k++)
				free(sec[k]);
			free(sec);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sec[j][m] = str[i++];
		sec[j][m] = 0;
	}

	sec[j] = NULL;
	return (sec);
}

