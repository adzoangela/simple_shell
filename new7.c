#include "main.h"

/**
 * custom_is_cmd - finds executable
 * @inf: struct
 * @path: path
 *
 * Return: 1 or 0
 */
int custom_is_cmd(info_struct *inf, char *adr)
{
	struct stat strrr;

	(void)inf;

	if (!adr || stat(adr, &strrr))
		return (0);

	if (strrr.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * custom_dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *custom_dup_chars(char *pts, int strt, int stp)
{
	static char buff[1024];
	int a = 0, b = 0;

	for (b = 0, a = strt; a < stp; a++)
		if (pts[a] != ':')
			buff[b++] = pts[a];
	buff[b] = 0;
	return (buff);
}

/**
 * custom_find_path - finds cmd
 * @inf: struct
 * @pts: string
 * @cmd: what to find
 * Return: full path
 */
char *custom_find_path(info_struct *inf, char *pts, char *cmd)
{
	int a = 0, current_pos = 0;
	char *path;

	if (!pts)
		return (NULL);
	if ((custom_strlen(cmd) > 2) && custom_start(cmd, "./"))
	{
		if (custom_is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pts[a] || pts[a] == ':')
		{
			path = custom_dup_chars(pts, current_pos, a);
			if (!*path)
				custom_strcat(path, cmd);
			else
			{
				custom_strcat(path, "/");
				custom_strcat(path, cmd);
			}
			if (custom_is_cmd(inf, path))
				return (path);
			if (!pts[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
