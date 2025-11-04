#include "main.h"

/**
 * strip_spaces - remove leading and trailing spaces in place
 * @s: string to strip
 *
 * Return: pointer to first non-space char (may be s itself)
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
 * @progname: program name to use in error messages
 */
void shell_loop(char *progname)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *cmd;

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

		execute_cmd(cmd, progname);
		free(line);
	}
}
