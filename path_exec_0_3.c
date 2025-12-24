#define _GNU_SOURCE
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     /* access, fork, execve */
#include <sys/wait.h>   /* waitpid */

/*
 * resolve_command:
 * 1) If cmd contains '/', treat it as a path (absolute or relative) and do NOT search PATH.
 * 2) Otherwise, search PATH using strtok on a duplicated copy of PATH.
 *
 * Returns:
 *  - 1 if an executable path was found and stored in 'out'
 *  - 0 if not found / not executable
 *
 * NOTE: This function does NOT fork. It only resolves the executable path.
 */
int resolve_command(const char *cmd, char *out, size_t outsz)
{
    char *path, *copy, *token;

    if (!cmd || !*cmd || !out || outsz == 0)
        return 0;

    /* Case A: command already contains '/', so it is a direct path */
    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
        {
            snprintf(out, outsz, "%s", cmd);
            return 1;
        }
        return 0;
    }

    /* Case B: search inside PATH */
    path = getenv("PATH");
    if (!path || path[0] == '\0')
        return 0;

    /*
     * strtok() modifies the string, so we must duplicate PATH first.
     * If strdup fails, copy will be NULL.
     */
    copy = strdup(path);
    if (!copy)
        return 0;

    token = strtok(copy, ":");
    while (token)
    {
        /* Build candidate full path: token + "/" + cmd */
        snprintf(out, outsz, "%s/%s", token, cmd);

        /* Check if this file exists and is executable */
        if (access(out, X_OK) == 0)
        {
            free(copy);
            return 1; /* found */
        }

        token = strtok(NULL, ":");
    }

    free(copy);
    return 0; /* not found */
}

/*
 * run_external:
 * - Resolves command path first.
 * - If not found: returns 127 and DOES NOT call fork().
 * - If found: forks, execve in child, wait in parent.
 *
 * Returns the exit status of the command, or 127 if not found.
 */
int run_external(char **argv, char **envp, const char *progname, int cmd_no)
{
    char full[1024];
    pid_t pid;
    int status;

    if (!argv || !argv[0])
        return 0;

    /* IMPORTANT requirement for 0.3: do NOT fork if command doesn't exist */
    if (!resolve_command(argv[0], full, sizeof(full)))
    {
        dprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
                progname ? progname : "shell", cmd_no, argv[0]);
        return 127;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        /* Child: execute the program */
        execve(full, argv, envp);

        /* execve returns only on error */
        perror("execve");
        _exit(126);
    }

    /* Parent: wait for child */
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    return 1;
}
