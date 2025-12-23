#include "shell.h"

/**
* main - Entry point for the simple shell
* @argc: Argument count
* @argv: Argument vector (program name)
* Return: Always 0
*/
int main(int argc, char **argv)
{
char *command;
char *program_name = argv[0];
(void)argc;

while (1)
{
if (isatty(STDIN_FILENO))
display_prompt();

/* Read command from user */
command = read_command();

/* Handle EOF (Ctrl+D) */
if (command == NULL)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
free(command);
exit(EXIT_SUCCESS);
}

/* Execute the command */
if (command[0] != '\0')
{
execute_command(command, program_name);
}

free(command);
}

return (0);
}
