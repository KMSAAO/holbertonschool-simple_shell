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
int execute_cmd(char **args, char *progname);

#endif /* MAIN_H */
