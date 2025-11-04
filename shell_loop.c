#include "main.h"

/**
 * shell_loop - main shell loop
 * @progname: program name to use in error messages
 *
 * Description: prompt -> getline -> execute -> repeat
 * Single-word commands only, no PATH, handle EOF.
 */
void shell_loop(char *progname)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

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

		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		execute_cmd(line, progname);
		free(line);
	}
}
