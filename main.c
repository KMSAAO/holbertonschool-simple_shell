#include "main.h"

/**
 * main - entry point for simple shell 0.1
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;

	shell_loop(argv[0]);
	return (0);
}
