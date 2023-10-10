#include "main.h"

/**
 * build_environ - build/populates environment linked list in main.h
 * @information: Struct containing arguments,
 * used to maintain constant function prototype.
 *
 * Return: 0 (Success)
 */

int build_environ(info_struct *information)
{
	list_struct *node = NULL;
	unsigned int i;

	for (i = 0; environ[i]; i++)
		append_list_node(&node, environ[i], 0);

	information->env = node;

	return (0);
}

/**
 * custom_my_env - prints the current environment
 * @info: invoke info struct
 *
 * Return: 0 (success)
 */

int custom_my_env(info_struct *information)
{
	print_text_list(information->env);
	return (0);
}

/**
 * custom_my_setenv - Initialize a new env var
 * @information: info_struct
 *
 *  Return: 0 (success)
 */

int custom_my_setenv(info_struct *information)
{
	if (information->argc != 3)
	{
		error_puts("error: Incorrect number of input arguements\n");
		return (1);
	}
	if (custom_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * custom_my_unsetenv - rm an env var
 * @information: info struct
 *
 * Return: 0 (success)
 */

int custom_my_unsetenv(info_struct *information)
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
