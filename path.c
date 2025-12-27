#include "shell.h"

/**
 * resolve_command - Resolve a command to a full executable path
 * @cmd: command name (e.g., "ls") or a path (e.g., "/bin/ls", "../hbtn_ls")
 * @out: output buffer to store resolved full path
 * @outsz: size of output buffer
 * @envp: environment array (may be NULL or empty)
 *
 * Return: 1 if resolved and executable (X_OK), 0 otherwise
 *
 * Notes:
 * - If cmd contains '/', it is treated as a direct path.
 * - If cmd has no '/', it is searched in PATH from envp.
 * - Empty PATH entries (leading/trailing ':' or '::') are treated as current dir.
 * - Uses only allowed functions (string.h funcs + access + getcwd + etc.).
 */
int resolve_command(char *cmd, char *out, size_t outsz, char **envp)
{
    char *path, *pwd;
    size_t cmdlen, dirlen, need;
    size_t i, start;

    if (!cmd || !*cmd || !out || outsz == 0)
        return 0;

    /* Case A: command already contains '/', so it is a direct path */
    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
        {
            if (strlen(cmd) + 1 > outsz)
                return 0;

            /* copy cmd into out safely (length already checked) */
            strcpy(out, cmd);
            return 1;
        }
        return 0;
    }

    /* Case B: search inside PATH from envp (no getenv allowed) */
    path = get_env_value(envp, "PATH");
    if (!path || path[0] == '\0')
        return 0;

    pwd = get_pwd(envp); /* may be NULL */
    cmdlen = strlen(cmd);

    /* Manual split PATH on ':' to preserve empty entries */
    start = 0;
    i = 0;
    while (1)
    {
        if (path[i] == ':' || path[i] == '\0')
        {
            dirlen = i - start;

            /* empty entry => current directory */
            if (dirlen == 0)
            {
                if (pwd && pwd[0] != '\0')
                {
                    /* build: pwd + "/" + cmd */
                    need = strlen(pwd) + 1 + cmdlen + 1;
                    if (need <= outsz)
                    {
                        /* out = pwd + "/" + cmd */
                        size_t k, pos = 0;

                        for (k = 0; pwd[k] != '\0'; k++)
                            out[pos++] = pwd[k];

                        out[pos++] = '/';

                        for (k = 0; cmd[k] != '\0'; k++)
                            out[pos++] = cmd[k];

                        out[pos] = '\0';

                        if (access(out, X_OK) == 0)
                            return 1;
                    }
                }
                else
                {
                    /* fallback: "./cmd" */
                    need = 2 + cmdlen + 1; /* "./" + cmd + '\0' */
                    if (need <= outsz)
                    {
                        size_t k, pos = 0;

                        out[pos++] = '.';
                        out[pos++] = '/';

                        for (k = 0; cmd[k] != '\0'; k++)
                            out[pos++] = cmd[k];

                        out[pos] = '\0';

                        if (access(out, X_OK) == 0)
                            return 1;
                    }
                }
            }
            else
            {
                /* Non-empty directory entry */
                need = dirlen + 1 + cmdlen + 1; /* dir + "/" + cmd + '\0' */
                if (need <= outsz)
                {
                    size_t k, pos;

                    /* copy dir substring */
                    for (k = 0; k < dirlen; k++)
                        out[k] = path[start + k];

                    pos = dirlen;

                    /* add '/' */
                    out[pos++] = '/';

                    /* copy cmd */
                    for (k = 0; cmd[k] != '\0'; k++)
                        out[pos++] = cmd[k];

                    out[pos] = '\0';

                    if (access(out, X_OK) == 0)
                        return 1;
                }
            }

            if (path[i] == '\0')
                break;

            start = i + 1;
        }

        i++;
    }

    return 0;
}
