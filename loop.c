#include "main.h"

/**
 * shell_loop - main loop of the shell
 *
 * Description: shows prompt if interactive, reads a line,
 * parses it, executes it, then repeats until EOF or "exit".
 */
void shell_loop(void)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		line = read_line();
		if (!line)
		{
			/* EOF (Ctrl+D) */
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		args = split_line(line);
		if (args && args[0])
			status = execute_cmd(args);
		else
			status = 1;

		free(line);
		free(args);
	}
}

