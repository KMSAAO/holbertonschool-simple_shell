#include "main.h"

extern char **environ;

/**
 * get_path_value - get PATH value from env
 *
 * Return: pointer to PATH string (not a copy), or NULL
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
 * find_in_path - build "dir/cmd" and check if executable
 * @cmd: command name (no slash)
 *
 * Return: malloc'ed string with full path if found, else NULL
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
 * execute_cmd - resolve command (direct or via PATH) then exec
 * @args: argv-like array (args[0] = command)
 * @progname: shell name for error messages
 *
 * Return: 1 to continue shell loop
 */
int execute_cmd(char **args, char *progname)
{
	pid_t pid;
	int status;
	char *cmd_path = NULL;

	/* case 1: user typed a path (/bin/ls, ./a.out, etc.) */
	if (strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: not found\n", progname);
			return (1);
		}
		cmd_path = args[0];
	}
	else
	{
		/* case 2: search in PATH */
		cmd_path = find_in_path(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: not found\n", progname);
			return (1);
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
	}

	return (1);
}
