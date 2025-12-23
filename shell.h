#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

/* Function Prototypes */
void display_prompt(void);
char *read_command(void);
void execute_command(char *command, char *program_name);
void handle_error(char *program_name, char *command);

/* external var for environment */
extern char **environ;

/* Macro Definitions */
#define BUFFER_SIZE (1024)
#define PROMPT "($)"
#define ERRFILE "No such file or directory\n"
#define ERRFOUND "not found\n"

#endif /* SHELL_H */
