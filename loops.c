#include "main.h"

/**
 * hash_batch - loop for main
 * @information: info struct
 * @agv: arg vec
 *
 * Return: 0 (success) 1 (failure)
 */

int hash_batch(info_struct *information, char **agv)
{
	ssize_t r = 0;
	int count = 0;

	while (r != -1 && count != -2)
	{
		reset_info(information);
		if (interactive_mode(information))
			custom_puts("$ ");
		error_putchar(RESET_BUF);
		r = obtain_input(information);
		if (r != -1)
		{
			info_start(information, agv);
			count = search_builtin_cmd(information);
			if (count == -1)
				search_command(information);
		}
		else if (interactive_mode(information))
			custom_putchar('\n');
		free1(information, 0);
	}
	history_write(information);
	free1(information, 1);
	if (!interactive_mode(information) && information->status)
		exit(information->status);
	if (count == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (count);
}

