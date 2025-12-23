#include "shell.h"
#include <ctype.h>  /* Add this include for isspace() */

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
    const char prompt[] = "($)";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

/**
 * trim_spaces - Removes leading and trailing spaces
 * @str: String to trim
 * Return: Pointer to trimmed string
 */
static char *trim_spaces(char *str)
{
    char *end;

    /* Trim leading spaces */
    while (isspace((unsigned char)*str))
        str++;

    /* If all spaces, return empty string */
    if (*str == '\0')
        return str;

    /* Trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    /* Write new null terminator */
    *(end + 1) = '\0';

    return str;
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
    char *trimmed;

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

    /* Trim leading and trailing whitespace */
    trimmed = trim_spaces(buffer);

    /* If trimmed string is different from buffer, copy it back */
    if (trimmed != buffer)
    {
        memmove(buffer, trimmed, strlen(trimmed) + 1);
    }

    return (buffer);
}
