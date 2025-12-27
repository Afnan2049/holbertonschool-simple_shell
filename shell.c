#include "shell.h"

/**
 * trim_spaces - Removes leading and trailing spaces
 * @str: String to trim
 * Return: Pointer to trimmed string
 */
/**
 * execute_command - Executes a command using execve
 * @argv: Array of arguments
 */
void execute_command(char **argv)
{
	pid_t pid;
	int status;

	if (access(argv[0], X_OK) != 0)
	{
		perror(argv[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}
