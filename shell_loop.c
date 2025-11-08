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

#include "main.h"

#define MAX_ARGS 64

/**
 * read_and_parse_line - reads input and parses it into args
 * @args: argument array to populate
 * @cmd_count: pointer to command count
 *
 * Return: line buffer (must be freed by caller) or NULL on EOF
 */
char *read_and_parse_line(char **args, int *cmd_count)
{
	char *line = NULL, *cmd, *token;
	size_t len = 0;
	ssize_t nread;
	int i = 0;

	if (isatty(STDIN_FILENO))
		printf("#cisfun$ ");

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	cmd = strip_spaces(line);
	if (cmd[0] == '\0')
	{
		free(line);
		return (NULL);
	}

	(*cmd_count)++;
	token = strtok(cmd, " \t");
	while (token && i < (MAX_ARGS - 1))
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	return (line);
}

/**
 * handle_command - handles builtins or external commands
 * @args: argument vector
 * @line: line buffer to free
 * @progname: program name
 * @cmd_count: command count
 * @status: pointer to current status
 *
 * Return: 1 to continue loop, 0 to exit loop
 */
int handle_command(char **args, char *line, char *progname,
		   int cmd_count, int *status)
{
	int j;

	if (args[0] == NULL)
	{
		free(line);
		return (1);
	}

	if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
	{
		free(line);
		return (0);
	}

	if (strcmp(args[0], "env") == 0 && args[1] == NULL)
	{
		for (j = 0; environ[j]; j++)
			printf("%s\n", environ[j]);
		free(line);
		return (1);
	}

	*status = execute_cmd(args, progname, cmd_count);
	free(line);
	return (1);
}

/**
 * shell_loop - main loop of the shell
 * @progname: program name to show in errors
 *
 * Return: last command exit status
 */
int shell_loop(char *progname)
{
	char *line;
	char *args[MAX_ARGS];
	int status = 0, cmd_count = 0;

	while (1)
	{
		line = read_and_parse_line(args, &cmd_count);
		if (!line)
			break;

		if (!handle_command(args, line, progname, cmd_count, &status))
			break;
	}

	return (status);
}
