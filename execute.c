#include "main.h"

/**
 * execute_cmd - executes a command
 * @args: argument vector
 *
 * Return: 0 to stop shell, 1 to continue
 */
int execute_cmd(char **args)
{
	pid_t pid;
	int status;

	if (strcmp(args[0], "exit") == 0)
		return (0);

	pid = fork();
	if (pid == 0)
	{
		/* child */
		if (execve(args[0], args, environ) == -1)
			perror("hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		/* parent */
		waitpid(pid, &status, 0);
	}

	return (1);
}

