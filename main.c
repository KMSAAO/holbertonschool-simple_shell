#include "main.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: exit status of last command
 */
int main(int argc, char **argv)
{
	(void)argc;

	return (shell_loop(argv[0]));
}
