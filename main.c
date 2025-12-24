#include "shell.h"

/**
 * main - entry point of the simple shell
 * @ac: argument count (unused)
 * @av: argument vector, used to get program name
 *
 * Description:
 * Reads user input line-by-line, increments a command counter
 * for each executed command, and passes both the input and
 * counter to the command execution handler.
 *
 * Return: Always 0
 */

int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	int cmd_count = 0;

	(void)ac;

	while (getline(&line, &len, stdin) != -1)
	{
		cmd_count++;
		execute_command(line, av[0], cmd_count);
	}
	free(line);
	return (0);
}
