#include "main.h"

/**
 * history_print - reads history
 * @information: struct
 *
 * Return: count (success), 0 (failure)
 */

int history_print(info_struct *information)
{
	int i, last = 0, lcount = 0;
	ssize_t filedesc, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = fetch_history(information);

	if (filename == NULL)
		return (0);

	filedesc = open(filename, O_RDONLY);
	free(filename);
	if (filedesc == -1)
		return (0);
	if (!fstat(filedesc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (buffer == NULL)
		return (0);
	rdlen = read(filedesc, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(filedesc);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			construct_history(information, buffer + last, lcount++);
			last = i + 1;
		}
	if (last != i)
		construct_history(information, buffer + last, lcount++);
	free(buffer);
	information->histcount = lcount;
	while (information->histcount-- >= HIST_MAXIMUM)
		delete_n_by_index(&(information->history), 0);
	history_renumber(information);
	return (information->histcount);
}

/**
 * fetch_history - gets history file
 * @information: struct
 *
 * Return: ptr containg history file
 */

char *fetch_history(info_struct *information)
{
	char *buffer, *directory;

	directory = get_environ(information, "HOME=");
	if (directory == NULL)
		return (NULL);

	buffer = malloc(sizeof(char) * (custom_strlen(directory) +
				custom_strlen(FILE_FOR_HIST) + 2));
	if (buffer == NULL)
		return (NULL);

	buffer[0] = 0;
	custom_strcpy(buffer, directory);
	custom_strcat(buffer, "/");
	custom_strcat(buffer, FILE_FOR_HIST);

	return (buffer);
}

/**
 * history_write - creates a file,
 * or appends to an existing file
 * @information: struct
 *
 * Return: 1 on success, else -1
 */
int history_write(info_struct *information)
{
	ssize_t filedesc;
	char *filename = fetch_history(information);
	list_struct *node = NULL;

	if (filename == NULL)
		return (-1);

	filedesc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (filedesc == -1)
		return (-1);

	for (node = information->history; node; node = node->next)
	{
		error_putsfd(node->str, filedesc);
		error_putsfd("\n", filedesc);
	}
	error_putfd(RESET_BUF, filedesc);
	close(filedesc);

	return (1);
}

/**
 * history_renumber - renumber hist after changes
 * @information: Struct containing info
 *
 * Return: hiscount
 */
int history_renumber(info_struct *information)
{
	list_struct *current_node = information->history;
	int i = 0;

	while (current_node)
	{
		current_node->num = i++;
		current_node = current_node->next;
	}
	return (information->histcount = i);
}

/**
 * construct_history - adds to hist linked list
 * @information: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @lcount: the history linecount, histcount
 *
 * Return: Always 0
 */
int construct_history(info_struct *information, char *buffer, int lcount)
{
	list_struct *current_node = NULL;

	if (information->history)
		current_node = information->history;
	append_list_node(&current_node, buffer, lcount);

	if (information->history == NULL)
		information->history = current_node;
	return (0);
}

