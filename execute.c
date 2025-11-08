#include "main.h"
#include <sys/wait.h>

extern char **environ;

/**
 * get_path_value - get PATH from environment
 *
 * Return: pointer to PATH value or NULL
 */
static char *get_path_value(void)
{
	int i;
	size_t len = strlen("PATH=");

	for (i = 0; environ && environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", len) == 0)
			return (environ[i] + len);
	}
	return (NULL);
}

/**
 * find_in_path - search for a command in PATH
 * @cmd: command name (no slash)
 *
 * Return: malloc'ed full path if found, or NULL
 */
static char *find_in_path(char *cmd)
{
	char *path = get_path_value();
	char *copy, *dir, *full;
	size_t len_dir, len_cmd;

	if (!path)
		return (NULL);

	copy = strdup(path);
	if (!copy)
		return (NULL);

	len_cmd = strlen(cmd);
	dir = strtok(copy, ":");
	while (dir)
	{
		len_dir = strlen(dir);
		full = malloc(len_dir + 1 + len_cmd + 1);
		if (!full)
		{
			free(copy);
			return (NULL);
		}

		strcpy(full, dir);
		full[len_dir] = '/';
		strcpy(full + len_dir + 1, cmd);

		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}

		free(full);
		dir = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}

/**
 * execute_cmd - resolve and execute a command
 * @args: argument vector
 * @progname: shell name (argv[0])
 * @cmd_count: current command number (for error message)
 *
 * Return: exit status of the command (127 if not found)
 */
int execute_cmd(char **args, char *progname, int cmd_count)
{
	pid_t pid;
	int status;
	char *cmd_path = NULL;

	/* if user typed a path */
	if (strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				progname, cmd_count, args[0]);
			return (127);
		}
		cmd_path = args[0];
	}
	else
	{
		/* search in PATH */
		cmd_path = find_in_path(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				progname, cmd_count, args[0]);
			return (127);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror(progname);
		if (cmd_path != args[0])
			free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(progname);
			if (cmd_path != args[0])
				free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd_path != args[0])
			free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (0);
}
