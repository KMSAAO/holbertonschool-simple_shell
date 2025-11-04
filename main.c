#include "main.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	(void)argc;

	shell_loop(argv[0]);
	return (0);
}
