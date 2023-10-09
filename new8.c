#include "main.h"

/**
 * hash_batch - shell loop
 * @inf: info struct
 * @av: argument vector
 * Return: 0 on success, 1 on error, or error code
 */
/*int hash_batch(info_struct *info, char **av)
{
	ssize_t a = 0;
	int builtin_ttt = 0;

	while (a != -1 && builtin_ttt != -2)
	{
		reset_info(info);
		if (interactive_mode(info))
			custom_puts(",kk,o$ ");
		error_putchar(RESET_BUF);
			a = obtain_input(info);
		if (a != -1)
		{
			info_start(info, av);
			builtin_ttt = search_builtin_cmd(info);
			if (builtin_ttt == -1)
				search_builtin_cmd(info);
		}
		else if (interactive_mode(info))
			custom_putchar('\n');
		free1(info, 0);
	}
	history_write(info);
	free1(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_ttt == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ttt);
}*/

/**
 * Search_builtin_cmd - searches builtin command
 * @info: the parameter
 * Return: -1, 0
 */
int search_builtin_cmd(info_struct *info)
{
	int i, built_rettt = -1;
	builtin_table builtintbll[] = {
		{"exit", custom_my_exit},
		{"env", custom_my_env},
		{"help", custom_myhelp},
		{"history", custom_my_history},
		{"setenv", custom_my_setenv},
		{"unsetenv", custom_my_unsetenv},
		{"cd", custom_mycd},
		{"alias", custom_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbll[i].type; i++)
		if (custom_strcmp(info->argv[0], builtintbll[i].type) == 0)
		{
			info->line_count++;
			built_rettt = builtintbll[i].func(info);
			break;
		}
	return (built_rettt);
}

/**
 * search_command - locates command in PATH
 * @info: the parameter
 * Return: void
 */
void search_command(info_struct *info)
{
	char *path = NULL;
	int a, b;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!check_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = custom_find_path(info, get_environ(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		custom_fork_cmd(info);
	}
	else
	{
		if ((interactive_mode(info) || get_environ(info, "PATH=")
					|| info->argv[0][0] == '/') && custom_is_cmd(info, info->argv[0]))
			custom_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			error_print(info, "not found\n");
		}
	}
}

/**
 * custom_fork_cmd - forks a an exec thread
 * @info: the parameter
 * Return: void
 */
void custom_fork_cmd(info_struct *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, obtain_environ(info)) == -1)
		{
			free1(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				error_print(info, "Permission denied\n");
		}
	}
}
