#include "shell.h"

/**
* execute_command - Executes a command
* @command: The command to execute
* @program_name: Name of the program
*/
void execute_command(char *command, char *program_name)
{
pid_t pid;
int status;
struct stat st;
char *args[2];

/* Check if command is an absolute path */
if (stat(command, &st) == 0)
{
if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
{
/* Fork a child process */
pid = fork();
if (pid == -1)
{
perror("fork");
return;
}

if (pid == 0) /* Child process */
{
args[0] = command;
args[1] = NULL;

if (execve(command, args, environ) == -1)
{
handle_error(program_name, command);
exit(EXIT_FAILURE);
}
}
else /* Parent process */
{
/* Wait for child to complete */
waitpid(pid, &status, 0);
}
return;
}
}

/* If we get here, command wasn't found or isn't executable */
handle_error(program_name, command);
}
/**
* handle_error - Handles and prints error messages
* @program_name: Name of the program (argv[0])
* @command: The command that failed
*/
void handle_error(char *program_name, char *command)
{
char error_msg[BUFFER_SIZE];
int len;

/* Format error message like sh: command: not found */
len = snprintf(error_msg, sizeof(error_msg),
"%s: 1: %s: not found\n", program_name, command);

if (len > 0 && len < (int)sizeof(error_msg))
write(STDERR_FILENO, error_msg, len);
}
