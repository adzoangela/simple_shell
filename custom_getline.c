#include "main.h"

/**
 * custom_getline - getline implemention
 * @information: struct
 * @ptr: adr of ptr to buf
 * @size: size ptr buffer
 * Return: count
 */

ssize_t custom_getline(info_struct *information, char **ptr, size_t *size)
{
	static char buffer[BUFFER_READ];
	static size_t i, len;
	unsigned int k;
	ssize_t r = 0, count = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && size)
		count = *size;
	if (i == len)
		i = len = 0;

	r = buffer_reader(information, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = custom_strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = custom_realloc(p, count, count ? count + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (count)
		custom_strncat(new_p, buffer + i, k - i);
	else
		custom_strncpy(new_p, buffer + i, k - i + 1);

	count += k - i;
	i = k;
	p = new_p;

	if (size)
		*size = count;
	*ptr = p;
	return (count);
}

/**
 * signal_helper - blocks ctrl+C
 * @sig: the signal number
 */

void signal_helper(int sig)
{
	(void)sig;

	custom_puts("\n");
	custom_puts("$ ");
	custom_putchar(RESET_BUF);
}


/**
 * buffer_input - buffers chained commands
 * @information: struct
 * @buffer: adr of buffer
 * @length: adr of variable length
 * Return: bytes read
 */

ssize_t buffer_input(info_struct *information, char **buffer, size_t *length)
{
	ssize_t count = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signal_helper);
		/*count = custom_getline(buffer, &len_p, stdin);*/
		count = custom_getline(information, buffer, &len_p);
		if (count > 0)
		{
			if ((*buffer)[count - 1] == '\n')
			{
				(*buffer)[count - 1] = '\0';
				count--;
			}
			information->linecount_flag = 1;
			hush_comments(*buffer);
			construct_history(information, *buffer, information->histcount++);
			if (custom_strchr(*buffer, ';')) /* is this a command chain?*/
			{
				*length = count;
				information->cmd_buf = buffer;
			}
		}
	}
	return (count);
}

/**
 * obtain_input - gets new line and removes the newline
 * @information: struct to store parameter
 * Return: bytes read
 */

ssize_t obtain_input(info_struct *information)
{
	static char *buffer;
	static size_t i, j;
	static size_t length;
	ssize_t count = 0;
	char **buf_parse = &(information->arg), *parse;

	custom_putchar(RESET_BUF);

	count = buffer_input(information, &buffer, &length);
	if (count == -1)
		return (-1);

	if (length)
	{
		j = i;
		parse = buffer + i;

		get_chain(information, buffer, &j, i, length);
		while (j < length)
		{
			if (search_chain(information, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			information->cmd_buf_type = CMD_NORM;
		}
		*buf_parse = parse;
		return (custom_strlen(parse));
	}

	*buf_parse = buffer;
	return (count);
}

/**
 * buffer_reader - reads from a buffer
 * @information: parameter struct
 * @buffer: buffer
 * @size: size
 * Return: bytes count
 */

ssize_t buffer_reader(info_struct *information, char *buffer, size_t *size)
{
	ssize_t count = 0;

	if (*size)
		return (0);

	count = read(information->readfd, buffer, BUFFER_READ);
	if (count >= 0)
		*size = count;

	return (count);
}

