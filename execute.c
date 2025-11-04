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
#include "main.h"

extern char **environ;

/**
 * get_path_value - returns the value of PATH from env
 *
 * Return: pointer to PATH value or NULL
 */
static char *get_path_value(void)
{
	int i;
	size_t len;

	if (!environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		len = strlen("PATH=");
		if (strncmp(environ[i], "PATH=", len) == 0)
			return (environ[i] + len);
	}
	return (NULL);
}

/**
 * find_in_path - search for command in PATH
 * @cmd: command name (no slash)
 *
 * Return: malloc'ed full path on success, or NULL if not found
 */
static char *find_in_path(char *cmd)
{
	char *path, *path_copy, *dir, *full;
	size_t len_dir, len_cmd;
	struct stat st;

	path = get_path_value();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	len_cmd = strlen(cmd);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		len_dir = strlen(dir);
		full = malloc(len_dir + 1 + len_cmd + 1);
		if (!full)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(full, dir);
		full[len_dir] = '/';
		strcpy(full + len_dir + 1, cmd);

		if (stat(full, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute_cmd - resolve command (absolute or from PATH) and exec
 * @args: argument vector (command + args)
 * @progname: shell name for error messages
 *
 * Return: 1 to continue loop
 */
int execute_cmd(char **args, char *progname)
{
	pid_t pid;
	int status;
	char *cmd_path = NULL;
	struct stat st;

	/* case 1: user typed a path like /bin/ls or ./a.out */
	if (strchr(args[0], '/'))
	{
		if (stat(args[0], &st) == -1)
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
