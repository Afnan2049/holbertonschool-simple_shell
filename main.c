#include "shell.h"

int main(int argc, char **argv, char **envp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[64];
    char *cmd;
    int i;
    int cmd_no = 0;

    (void)argc;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            free(line);
            return (0);
        }

        cmd_no++; /* counts every read line */

        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        cmd = trim_spaces(line);
        if (!cmd || *cmd == '\0')
            continue;

        /* tokenize */
        i = 0;
        args[i] = strtok(cmd, " \t");
        while (args[i] != NULL && i < 63)
        {
            i++;
            args[i] = strtok(NULL, " \t");
        }
        args[i] = NULL;

        if (args[0] != NULL)
            run_external(args, envp, argv[0], cmd_no);
    }

    free(line);
    return (0);
}
