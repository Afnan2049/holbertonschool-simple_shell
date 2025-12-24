#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Utilities */
char *trim_spaces(char *str);
int is_executable(char *path);
char *get_full_path(char *cmd);

/* Shell execution */
void execute_command(char **argv);

#endif /* SHELL_H */

