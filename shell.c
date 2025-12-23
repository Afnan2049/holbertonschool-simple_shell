#include "shell.h"

/**
* display_prompt - Displays the shell prompt
*/
void display_prompt(void)
{
write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
}

/**
* read_command - Reads a command from standard input
* Return: Pointer to the command string, or NULL on EOF
*/
char *read_command(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t chars_read;

/* Read line from stdin */
chars_read = getline(&buffer, &bufsize, stdin);

if (chars_read == -1)
{
free(buffer);
return (NULL);
}

/* Remove newline character */
if (chars_read > 0 && buffer[chars_read - 1] == '\n')
buffer[chars_read - 1] = '\0';

return (buffer);
}
