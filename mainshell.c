#include "mainshell.h"

/**
 * main - the main function for the simple shell
 * @argc: number of arguments
 * @argv: arguments
 * Return: 0 on success 1 otherwise
 */
int main(int argc, char **argv)
{
	size_t mode_inter = 0, length = 0, compt = 0, exit_status = 0;
	char *line = NULL;
	ssize_t letters_read = 0;

	if (isatty(STDIN_FILENO))
		mode_inter = 1;
	while (1)
	{
		if (mode_inter == 1)
			write(2, "$ ", 2);
		compt++;
		letters_read = getline(&line, &length, stdin);
		if (letters_read != -1)
		{
			argv = divide(line, &argc);
			if (argv != NULL)
			{
				if (argc != 0)
					exit_status = execute(argv, compt);
				compt = 0;
				while (argv[compt] != NULL)
				{
					free(argv[compt]);
					compt++;
				}
				free(argv);
			}
		}
		else
		{
			if (mode_inter == 1)
				write(2, "\n", 2);
			free(line);
			return (exit_status);
		}
	}
	free(line);
	return (exit_status);
}
