#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function Prototypes */
void display_prompt(void);
char *read_line(void);
void execute_command(char *command);
int is_valid_command(char *command);

/* Macro Definitions */
#define BUFFER_SIZE (1024)
#define PROMPT_TEXT "$ "
#define ERRFILE "No such file or directory\n"
#define ERRFOUND "not found\n"

#endif /* SHELL_H */
