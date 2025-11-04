#include "main.h"

#define MAX_ARGS 64

/**
 * strip_spaces - remove leading and trailing spaces/tabs
 * @s: string to strip
 *
 * Return: pointer to first non-space char
 */
static char *strip_spaces(char *s)
{
	char *end;

	while (*s == ' ' || *s == '\t')
		s++;

	if (*s == '\0')
		return (s);

	end = s + strlen(s) - 1;
	while (end > s && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	return (s);
}

/**
 * shell_loop - main loop of the shell
 * @progname: program name to show in errors
 *
 * Return: last command exit status
 */
int shell_loop(char *progname)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *cmd;
	char *token;
	char *args[MAX_ARGS];
	int i;
	int status = 0;
	int cmd_count = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		line = NULL;
		len = 0;
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		cmd = strip_spaces(line);
		if (cmd[0] == '\0')
		{
			free(line);
			continue;
		}

		/* got a real command line */
		cmd_count++;

		i = 0;
		token = strtok(cmd, " \t");
		while (token && i < (MAX_ARGS - 1))
		{
			args[i++] = token;
			token = strtok(NULL, " \t");
		}
		args[i] = NULL;

		if (args[0] != NULL)
			status = execute_cmd(args, progname, cmd_count);

		free(line);
	}

	return (status);
}
