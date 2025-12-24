#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[64];
    char *command;
    int i;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        command = trim_spaces(line);
        if (*command == '\0')
            continue;

        /* This part handles the arguments */
        i = 0;
        argv[i] = strtok(command, " \t");
        while (argv[i] != NULL && i < 63)
        {
            i++;
            argv[i] = strtok(NULL, " \t");
        }
        argv[i] = NULL;

        if (argv[0] != NULL)
            execute_command(argv);
    }
    free(line);
    return (0);
}
