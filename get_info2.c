#include "main.h"

/**
 * info_start - init info_struct
 * @information: struct
 * @agv: arguments
 */
void info_start(info_struct *information, char **agv)
{
	int i = 0;

	information->fname = agv[0];
	if (information->arg)
	{
		information->argv = custom_strtow(information->arg, " \t");
		if (information->argv == NULL)
		{
			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = custom_strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (i = 0; information->argv && information->argv[i]; i++)
			;
		information->argc = i;

		alias_exchange(information);
		vars_exchange(information);
	}
}

/**
 * reset_info - clears info_struct
 * @information: struct
 *
 * Return: Nothing
 */

void reset_info(info_struct *information)
{
	information->arg = NULL;

	information->argv = NULL;

	information->path = NULL;

	information->argc = 0;
}

/**
 * free1 - free info_struct
 * @information: struct
 * @entire: all fields
 */

void free1(info_struct *information, int entire)
{
	free2(information->argv);
	information->argv = NULL;
	information->path = NULL;

	if (entire)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			free_text_list(&(information->env));
		if (information->history)
			free_text_list(&(information->history));
		if (information->alias)
			free_text_list(&(information->alias));
		free2(information->environ);
			information->environ = NULL;
		free3((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		custom_putchar(RESET_BUF);
	}
}
