#include "shell.h"

/**
* run_shell - Main loop of the shell
* @prog_name: name of the shell program
*/
void run_shell(char *prog_name)
{
char *lineptr = NULL;
size_t n = 0;
ssize_t nread;
int cmd_count;

while (1)
{
if (isatty(STDIN_FILENO))
printf("%s", PROMPT);

nread = getline(&lineptr, &n, stdin);
if (nread == -1)
break;

if (nread > 1 && !is_only_spaces(lineptr))
{
cmd_count++;
execute_command(lineptr, prog_name, cmd_count);
}
}

free(lineptr);
}
/**
* is_only_spaces - checks if a string contains only whitespace
* @str: input string
*
* Return: 1 if only spaces, 0 otherwise
*/
int is_only_spaces(char *str)
{
int i = 0;

while (str[i])
{
if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
return (0);
i++;
}
return (1);
}
