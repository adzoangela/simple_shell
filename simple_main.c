#include "main.h"

/**
 * main - Entry point
 * @agc: argument count
 * @agv: argument vector
 *
 * Return: 0 (Success), 1 (Failure)
 */

int main(int agc, char **agv)
{
	info_struct information[] = { INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_descriptor)
			: "r" (file_descriptor));

	if (agc == 2)
	{
		file_descriptor = open(agv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				custom_puts(agv[0]);
				custom_puts(": 0: Can't open ");
				custom_puts(agv[1]);
				custom_putchar('\n');
				custom_putchar(RESET_BUF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = file_descriptor;
	}

	build_environ(information);
	history_print(information);
	hash_batch(information, agv);

	return (EXIT_SUCCESS);
}
