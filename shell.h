#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 102
#define PROMPT "($)"

extern char **environ;

void run_shell(char *prog_name);
int execute_command(char *line, char *prog_name, int cmd_count);
char *resolve_command_path(char **argv, char *prog_name, int cmd_count);
int is_only_spaces(char *str);
char *find_path(char *command);
char *get_env_value(char *name);

#endif
