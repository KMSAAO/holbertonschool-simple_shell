#include "main.h"

#define MAX_ARGS 64

/**
 * strip_spaces - remove leading/trailing spaces
 * @s: string
 *
 * Return: pointer to first non-space
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
 * shell_loop - main shell loop
 * @progname: program name used in error messages
 */
void shell_loop(char *progname)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *cmd;
	char *token;
	char *args[MAX_ARGS];
	int i;

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

		/* tokenize into args[] */
		i = 0;
		token = strtok(cmd, " \t");
		while (token && i < (MAX_ARGS - 1))
		{
			args[i++] = token;
			token = strtok(NULL, " \t");
		}
		args[i] = NULL;

		if (args[0] != NULL)
			execute_cmd(args, progname);

		free(line);
	}
}
