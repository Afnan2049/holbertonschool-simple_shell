#include "shell.h"

/**
 * builtin_env - prints current environment
 * @envp: environment array (may be NULL)
 * Return: 0
 */
int builtin_env(char **envp)
{
    int i;

    if (!envp)
        return 0;

    for (i = 0; envp[i]; i++)
    {
        write(STDOUT_FILENO, envp[i], strlen(envp[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    return 0;
}
