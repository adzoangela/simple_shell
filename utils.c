#include "main.h"

/**
 * search_chain - for chain delim
 * @information: struct
 * @buffer: char buffer
 * @pos: adr of current position in buffer
 * Return: 1 (success), 0 otherwise
 */

int search_chain(info_struct *information, char *buffer, size_t *pos)
{
	unsigned int j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_OR;
	}

	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_AND;
	}

	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		information->cmd_buf_type = CMD_CHAIN;
	}

	else
		return (0);

	*pos = j;

	return (1);
}

/**
 * get_chain - check chain status
 * @information: struct
 * @buffer: buffer
 * @pos: adr of cur position in buffer
 * @i: starting position in buffer
 * @length: length of buffer
 */

void get_chain(info_struct *information, char *buffer,
			size_t *pos, size_t i, size_t length)
{
	size_t j = *pos;

	if (information->cmd_buf_type == CMD_AND)
	{
		if (information->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}

	if (information->cmd_buf_type == CMD_OR)
	{
		if (!information->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}
	*pos = j;
}

/**
 * alias_exchange - replaces an aliases in the tokenized string
 * @information: the parameter struct
 * Return: 1 (success), 0 otherwise
 */

int alias_exchange(info_struct *information)
{
	int i;
	list_struct *current_node;
	char *pos;

	/*exhange alias*/
	for (i = 0; i < 10; i++)
	{
		current_node = list_prefix(information->alias, information->argv[0], '=');
		if (current_node == NULL)
			return (0);

		free(information->argv[0]);

		pos = custom_strchr(current_node->str, '=');
		if (pos == NULL)
			return (0);
		pos = custom_strdup(pos + 1);
		if (pos == NULL)
			return (0);

		information->argv[0] = pos;
	}

	return (1);
}

/**
 * vars_exchange - replace variables in tokenized string
 * @information: struct
 * Return: 1 (success), 0 otherwise
 */
int vars_exchange(info_struct *information)
{
	int i = 0;
	list_struct *current_node;

	for (i = 0; information->argv[i]; i++)
	{
		if (information->argv[i][0] != '$' || !information->argv[i][1])
			continue;

		if (!custom_strcmp(information->argv[i], "$?"))
		{
			string_exchange(&(information->argv[i]),
					custom_strdup(conv_num(information->status, 10, 0)));
			continue;
		}
		if (!custom_strcmp(information->argv[i], "$$"))
		{
			string_exchange(&(information->argv[i]),
					custom_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		current_node = list_prefix(information->env, &information->argv[i][1], '=');
		if (current_node)
		{
			string_exchange(&(information->argv[i]),
					custom_strdup(custom_strchr(current_node->str, '=') + 1));
			continue;
		}
		string_exchange(&information->argv[i], custom_strdup(""));

	}
	return (0);
}

/**
 * string_exchange - exchange string
 * @old_adr: address -old string
 * @new_adr: new string address
 * Return: 1 if replaced, 0 otherwise
 */

int string_exchange(char **old_adr, char *new_adr)
{
	free(*old_adr);
	*old_adr = new_adr;

	return (1);
}

