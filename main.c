#include "main.h"

/**
 * main - entry point for the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	shell_loop();

	return (0);
}

#include "main.h"

/**
 * main - entry point for the simple shell 0.1
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
