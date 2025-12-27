#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>     /* isatty, write, access, fork, execve */
#include <stdlib.h>     /* malloc, free, exit */
#include <stdio.h>      /* getline, fprintf, perror */
#include <string.h>     /* all string.h funcs (strlen, strcpy, strchr, strncmp, strtok...) */
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /* waitpid, macros */

extern char **environ;

/* trimming */
char *trim_spaces(char *str);

/* env helpers (no getenv, no strdup) */
char *get_env_value(char **envp, const char *name);
char *strdup_allowed(const char *s);
char *get_pwd(char **envp);

/* path resolution */
int resolve_command(char *cmd, char *out, size_t outsz, char **envp);

/* execute */
int run_external(char **argv, char **envp, const char *progname, int cmd_no);

#endif /* SHELL_H */
