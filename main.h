#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * struct builtin_s - builtin commands
 * @name: name of the builtin command
 * @func: function to handle the builtin
 */
typedef struct builtin_s
{
	char *name;
	int (*func)(char **args);
} builtin_t;

/* main shell loop */
void shell_loop(void);

/* helpers */
char *read_line(void);
char **split_line(char *line);
int execute_cmd(char **args);

/* builtins (you can fill later) */
int shell_exit(char **args);
int shell_env(char **args);

#endif /* MAIN_H */
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void shell_loop(char *progname);
char *read_line(void);
int execute_cmd(char *cmd, char *progname);

#endif /* MAIN_H */
