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

#include "main.h"

extern char **environ;

/**
 * execute_cmd - forks and executes a command (no args)
 * @cmd: command to execute (full path required)
 * @progname: name of the shell (for perror)
 *
 * Return: 1 always (we always continue the loop)
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
		/* child: try to exec using exact path typed */
		if (execve(cmd, argv, environ) == -1)
		{
			perror(progname);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* parent: wait for child */
		waitpid(pid, &status, 0);
	}

	return (1);
}
