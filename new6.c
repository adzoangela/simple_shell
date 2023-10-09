#include "main.h"

/**
 * obtain_environ - returns the string array
 * @inf: structure
 * Return: Always 0
 */
char **obtain_environ(info_struct *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = lists_str(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * custom_unsetenv - discard environment variable
 * @inf: containing potential arguments.
 *  Return: 1, 0
 * @var: the string
 */
int custom_unsetenv(info_struct *inf, char *varr)
{
	list_struct *nd = inf->env;
	size_t a = 0;
	char *b;

	if (!nd || !varr)
		return (0);

	while (nd)
	{
		b = custom_start(nd->str, varr);
		if (b && *b == '=')
		{
			inf->env_changed = delete_n_by_index(&(inf->env), a);
			a = 0;
			nd = inf->env;
			continue;
		}
		nd = nd->next;
		a++;
	}
	return (inf->env_changed);
}

/**
 * custom_setenv - set a new env
 * @inf: contains arguments
 * @varr: string
 * @val: string
 *  Return: Always 0
 */
int custom_setenv(info_struct *inf, char *varr, char *val)
{
	char *buffer = NULL;
	list_struct *nd;
	char *b;

	if (!varr || !val)
		return (0);

	buffer = malloc(custom_strlen(varr) + custom_strlen(val) + 2);
	if (!buffer)
		return (1);
	custom_strcpy(buffer, varr);
	custom_strcat(buffer, "=");
	custom_strcat(buffer, val);
	nd = inf->env;
	while (nd)
	{
		b = custom_start(nd->str, varr);
		if (b && *b == '=')
		{
			free(nd->str);
			nd->str = buffer;
			inf->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	append_list_node(&(inf->env), buffer, 0);
	free(buffer);
	inf->env_changed = 1;
	return (0);
}
