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
	int status = 0;

	signal(SIGINT, sig_handler);
	while (1)
	{
		int length = 0, validation = 0;

		buffer = _prompt();
		length = _get_length(buffer);
		argv = (char **)malloc(sizeof(char *) * length);
		if (argv == NULL)
		{
			perror("Unable to allocate argv");
			exit(1);
		}
		_init_argv(argv, length);
		_get_argv(buffer, argv, length);
		validation = _validate_argv(argv, buffer);
		if (validation == 1)
			continue;
		if (validation == 2)
			exit(0);
		status = _execute_command(argv, buffer, _argv);
	}

	return (status);
}

/**
 * _print_env - print the environment
 * @argv: the arguments
 * @buffer: the buffer
 */
void _print_env(char **argv, char *buffer)
{
	int i = 0;
	char *new_line = "\n";

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, new_line, _strlen(new_line));
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
 * Return: 0 on success
 */
int _execute_command(char **argv, char *buffer, char **_argv)
{
	char *command = NULL;
	int status = 0;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(_argv[0]);
		return (1);
	}
	if (child_pid == 0)
	{
		if (*argv[0] != '/' && *argv[0] != '.')
		{
			list_s *results = NULL;

			results = _get_env_values("PATH");
			command = _get_location(results, argv[0]);
			if (!command)
				command = argv[0];
		}
		else
			command = argv[0];

		if (_strcmp(command, "env") == 0)
			_print_env(argv, buffer);

		if (execve(command, argv, environ) == -1)
			perror(_argv[0]);

		exit(127);
	}
	else
	{
		wait(&status);
		free(argv);
		free(buffer);
		return (status);
	}
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

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}
