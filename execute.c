#include "main.h"

extern char **environ;

/**
 * execute_cmd - fork and exec a command with optional args
 * @args: NULL-terminated array of strings (argv)
 * @progname: shell name for perror
 *
 * Return: 1 to continue loop
 */
int execute_cmd(char **args, char *progname)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(progname);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(progname);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (1);
}
