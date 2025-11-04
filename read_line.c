#include "main.h"

/**
 * read_line - reads a line from stdin
 *
 * Return: pointer to the line (must be freed), or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

#include "main.h"

/**
 * read_line - wrapper for getline (not used in shell_loop for now)
 *
 * Return: line read (must be freed) or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}
