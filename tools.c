#include "mainshell.h"
/**
 * divide - divide the line into multiple elements
 * @line: the input line to be divided
 * @argc: number of arguments
 * Return: an array of elements
 */
char **divide(char *line, int *argc)
{
	char **element = NULL, *result;
	int compt = 0;

	result = strtok(line, " \n\t");
	while (result != NULL)
	{
		element = realloc(element, sizeof(char *) * (compt + 1));
		if (element == NULL)
			return (NULL);
		element[compt] = strdup(result);
		compt++;
		result = strtok(NULL, " \n\t");
	}
	*argc = compt;
	return (element);
}

/**
 * execute - executes the line of command with arguments
 * @argv: arguments
 * @compt: number of arguments
 * Return: exit status of execve, fork and 127 in path not found
 */
int execute(char **argv, int compt)
{
	int status, exit_status;
	pid_t sub_p;
	char *command_path = NULL, buffer[12];

	command_path = find_path(argv[0]);
	if (command_path == NULL)
	{
		write(2, "./hsh: ", strlen("./hsh: "));
		int_to_str(compt, buffer);
		write(2, buffer, strlen(buffer));
		write(2, ": ", 2);
		write(2, argv[0], strlen(argv[0]));
		write(2, ": not found\n", strlen(" : not found\n"));
		return (127);
	}
	else
	{
		sub_p = fork();
		if (sub_p < 0)
			return (-1);
		else if (sub_p == 0)
		{
			if (execve(command_path, argv, environ) == -1)
				return (-1);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
			}
		}
		free(command_path);
	}
	return (exit_status);
}
/**
 *find_path - find the command path
 * @str: the command line
 * Return: path for the command if found
 */
char *find_path(char *str)
{
	char *existing_path, *sub_path, *cmd_path;
	int length, sub_length;

	if (access(str, X_OK) == 0)
		return (strdup(str));
	existing_path = getenv("PATH");
	if (existing_path == NULL)
		return (NULL);
	length = strlen(str);
	sub_path = strtok(existing_path, ":");
	while (sub_path != NULL)
	{
		sub_length = strlen(sub_path);
		cmd_path = malloc(sub_length + length + 2);
		if (cmd_path == NULL)
			return (NULL);
		strcpy(cmd_path, sub_path);
		strcat(cmd_path, "/");
		strcat(cmd_path, str);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		sub_path = strtok(NULL, ":");
	}
	return (NULL);
}
