#include "shell.h"

/**
* tokenize_input - split input line into arguments
* @line: input line
* @argv: array to fill
*
* Return: number of arguments
*/
int tokenize_input(char *line, char **argv)
{
int argc = 0;
char *token = strtok(line, " \t\n");

while (token && argc < BUFFER_SIZE - 1)
{
argv[argc++] = token;
token = strtok(NULL, " \t\n");
}

argv[argc] = NULL;
return (argc);
}

/**
* resolve_command_path - find full path of a command
* @argv: argument vector
* @prog_name: program name
* @cmd_count: command counter for error messages
*
* Return: pointer to path or NULL
*/
char *resolve_command_path(char **argv, char *prog_name, int cmd_count)
{
char *cmd_path;

if (strchr(argv[0], '/'))
return (argv[0]);

cmd_path = find_path(argv[0]);
if (!cmd_path)
{
fprintf(stderr, "%s: %d: %s: not found\n", prog_name, cmd_count, argv[0]);
return (NULL);
}

return (cmd_path);
}
/**
* execute_command - executes a command with arguments
* @line: input line
* @prog_name: program name
* @cmd_count: command counter for error messages
*
* Return: status code
*/
int execute_command(char *line, char *prog_name, int cmd_count)
{
pid_t pid;
char *argv[BUFFER_SIZE];
char *cmd_path;
int argc;

argc = tokenize_input(line, argv);
if (argc == 0)
return (0);

cmd_path = resolve_command_path(argv, prog_name, cmd_count);
if (!cmd_path)
return (127);

pid = fork();
if (pid == 0)
{
execve(cmd_path, argv, environ);
perror(prog_name);
exit(1);
}
else
{
wait(NULL);
}

if (cmd_path != argv[0])
free(cmd_path);

return (0);
}
/**
* find_path - search for a command in PATH
* @command: command name
*
* Return: full path (malloc'ed) or NULL
*/
char *find_path(char *command)
{
char *path = get_env_value("PATH");
char *path_copy, *dir, full_path[1024];

if (!path)
return (NULL);

path_copy = strdup(path);
if (!path_copy)
return (NULL);

dir = strtok(path_copy, ":");
while (dir)
{
snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (strdup(full_path));
}

dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}
/**
* get_env_value - get value of an environment variable
* @name: variable name (e.g. "PATH")
*
* Return: pointer to value or NULL
*/
char *get_env_value(char *name)
{
int i = 0;
size_t len = strlen(name);

while (environ[i])
{
if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
return (environ[i] + len + 1);
i++;
}
return (NULL);
}
