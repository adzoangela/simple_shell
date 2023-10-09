#include "main.h"

/**
 * custom_my_exit - exits
 * @info: Structure for argument
 * Return: exits
 */
int custom_my_exit(info_struct *info)
{
	int exitc;

	if (info->argv[1])
	{
		exitc = error_atoi(info->argv[1]);
		if (exitc == -1)
		{
			info->status = 2;
			error_print(info, "wrong number: ");
			error_puts(info->argv[1]);
			error_putchar('\n');
			return (1);
		}
		info->err_num = error_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * custom_mycd - changes the current directory
 * @info: Structure with  potential arguments
 * Return: Always 0
 */
int custom_mycd(info_struct *info)
{
	char *s, *dirr, buff[1024];
	int cdir_rettt;

	s = getcwd(buff, 1024);
	if (!s)
		custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirr = get_environ(info, "HOME=");
		if (!dirr)
			cdir_rettt =
				chdir((dirr = get_environ(info, "PWD=")) ? dirr : "/");
		else
			cdir_rettt = chdir(dirr);
	}
	else if (custom_strcmp(info->argv[1], "-") == 0)
	{
		if (get_environ(info, "OLDPWD="))
		{
			custom_puts(s);
			custom_putchar('\n');
			return (1);
		}
		custom_puts(get_environ(info, "OLDPWD=")), custom_putchar('\n');
		cdir_rettt =
			chdir((dirr = get_environ(info, "OLDPWD=")) ? dirr : "/");
	}
	else
		cdir_rettt = chdir(info->argv[1]);
	if (cdir_rettt == -1)
	{
		error_print(info, "no cd to ");
		error_puts(info->argv[1]), error_putchar('\n');
	}
	else
	{
		custom_setenv(info, "OLDPWD", get_environ(info, "PWD="));
		custom_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * custom_myhelp - changes current directory
 * @info: Structure containing arguments
 * Return: Always 0
 */
int custom_myhelp(info_struct *info)
{
	char **argg_array;

	argg_array = info->argv;
	custom_puts("help call works \n");
	if (0)
		custom_puts(*argg_array);
	return (0);
}
