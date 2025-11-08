#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int shell_loop(char *progname);
char *strip_spaces(char *s);
int execute_cmd(char **args, char *progname, int cmd_count);
char *read_and_parse_line(char **args, int *cmd_count);
int handle_command(char **args, char *line, char *progname,
		   int cmd_count, int *status);

extern char **environ;

#endif /* MAIN_H */
