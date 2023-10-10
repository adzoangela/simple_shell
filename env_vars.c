#include "main.h"

/**
 * custom_env - current env
 * @information: Struct
 *
 * Return: 0 (Success)
 */

int custom_env(info_struct *information)
{
	print_text_list(information->env);

	return (0);
}

/**
 * get_environ - environ variable value
 * @information: Struct
 * @name: environment variable name
 * Return: ptr to value
 */

char *get_environ(info_struct *information, const char *name)
{
	list_struct *current_node = information->env;
	char *pos;

	while (current_node)
	{
		pos = needle_check(current_node->str, name);
		if (pos && *pos)
			return (pos);

		current_node = current_node->next;
	}

	return (NULL);
}

/**
 * custom_mysetenv - setenv()
 * @information: Struct
 *  Return: 0 (success)
 */

int custom_mysetenv(info_struct *information)
{
	if (information->argc != 3)
	{
		error_puts("Number of arguements incorrect\n");
		return (1);
	}

	if (custom_setenv(information, information->argv[1], information->argv[2]))
		return (0);

	return (1);
}

/**
 * custom_myunsetenv - Remove an environment variable
 * @information: Struct
 *
 * Return: 0 (success)
 */

int custom_myunsetenv(info_struct *information)
{
	int i;

	if (information->argc == 1)
	{
		error_puts("Too few arguements.\n");
		return (1);
	}

	for (i = 1; i <= information->argc; i++)
		custom_unsetenv(information, information->argv[i]);

	return (0);
}

/**
 * custom_env_list - populates env list
 * @information: info_struct
 *
 * Return: 0 (success)
 */

int custom_env_list(info_struct *information)
{
	list_struct *current_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_list_node(&current_node, environ[i], 0);

	information->env = current_node;

	return (0);
}
