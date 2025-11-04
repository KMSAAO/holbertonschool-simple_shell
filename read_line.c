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

