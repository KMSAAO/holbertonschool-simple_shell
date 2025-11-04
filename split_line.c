#include "main.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * split_line - splits a line into tokens
 * @line: line to split
 *
 * Return: NULL-terminated array of tokens
 */
char **split_line(char *line)
{
	int bufsize = TOK_BUFSIZE, i = 0;
	char **tokens = NULL;
	char *token = NULL;

	tokens = malloc(sizeof(char *) * bufsize);
	if (!tokens)
		return (NULL);

	token = strtok(line, TOK_DELIM);
	while (token)
	{
		tokens[i++] = token;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[i] = NULL;

	return (tokens);
}

