#include "shell.h"

/**
 * main - main function
 * @_argc: number of arguments
 * @_argv: the arguments
 * Return: 0 on success
 */
int main(__attribute__((unused)) int _argc, char *_argv[])
{
	char *buffer = NULL;
	char **argv = NULL;
	pid_t child_pid;
	int status, flag_exit = 0;

	do {
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(_argv[0]);
			return (1);
		}
		if (child_pid == 0)
		{
			int length = 0;

			buffer = _prompt(&flag_exit);
			length = _get_length(buffer);
			argv = (char **)malloc(sizeof(char *) * length);
			if (argv == NULL)
			{
				perror("Unable to allocate argv");
				exit(1);
			}
			_init_argv(argv, length);
			_get_argv(buffer, argv, length);
			_validate_argv(argv, buffer);
			if (_strcmp(argv[0], "env") == 0)
				_print_env(argv, buffer);
			_execute_command(argv, buffer, _argv);
			if (flag_exit == 1)
				return (1);
			return (0);
		}
		else
			wait(&status);
	} while (status == 0);
	return (0);
}

/**
 * _print_env - print the environment
 * @argv: the arguments
 * @buffer: the buffer
 */
void _print_env(char **argv, char *buffer)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	free(argv);
	free(buffer);
	exit(0);
}

/**
 * _execute_command - execute the command
 * @argv: the arguments
 * @buffer: the buffer
 * @_argv: the arguments
 */
void _execute_command(char **argv, char *buffer, char **_argv)
{
	char *command = NULL;

	if (*argv[0] != '/' && *argv[0] != '.')
	{
		list_s *results = NULL;

		results = _get_env_values("PATH");
		command = _get_location(results, argv[0]);
		if (!command)
		{
			command = argv[0];
		}
	}
	else
	{
		command = argv[0];
	}

	if (execve(command, argv, environ) == -1)
	{
		perror(_argv[0]);
	}
	free(argv);
	free(buffer);
}

/**
 * _get_location - get the location of the command
 * @dirs: the directories
 * @command: the command
 * Return: the location
 */
char *_get_location(list_s *dirs, char *command)
{
	char *temp = NULL;
	struct stat status;

	while (dirs)
	{
		temp = malloc(dirs->len + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->str);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &status) == 0)
		{
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}
	return (NULL);
}
