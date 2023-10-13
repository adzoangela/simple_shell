#include "main.h"

/**
 * error_putfd - writes the character c to given fd
 * @ch: The character to print
 * @fd: The filedesc to write t
 * Return: 1(success).
 */
int error_putfd(char ch, int fd)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (ch == RESET_BUF || i >= MAX_BUFFER_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}

	if (ch != RESET_BUF)
		buffer[i++] = ch;

	return (1);
}

/**
 * list_prefix - returns node whose string starts with prefix
 * @head: pointer to list head
 * @pref: string to match
 * @c: the next character after prefix to match
 * Return: match node
 */

list_struct *list_prefix(list_struct *head, char *pref, char c)
{
	char *p = NULL;

	while (head)
	{
		p = needle_check(head->str, pref);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * interactive_mode - returns true if shell is interactive mode
 * @information: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */

int interactive_mode(info_struct *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}

