#include "main.h"

extern char **environ;

/**
 * execute_cmd - fork and exec a single-word command
 * @cmd: command to run (must be full path, no args)
 * @progname: shell name to print in errors
 *
 * Return: 1 (continue shell loop)
 */
int execute_cmd(char *cmd, char *progname)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(progname);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(cmd, argv, environ) == -1)
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
