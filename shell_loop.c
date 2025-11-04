#include "main.h"

/**
 * shell_loop - main loop of the shell
 * @progname: name of the program (for error messages)
 *
 * Description: displays a prompt (if interactive), reads one line,
 * executes it (only single-word commands), and repeats until EOF.
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

		/* remove trailing newline */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* empty line -> show prompt again */
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		execute_cmd(line, progname);
		free(line);
	}
}
