#include "shell.h"

/**
 * main - main function
 * @argc: number of arguments
 * @argv: the arguments
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *buffer = NULL;
	char **_argv = NULL;
	int status = 0;
	int counter = 0;

	if (argc != 1)
		return (2);

	signal(SIGINT, sig_handler);
	while (1)
	{
		int length = 0, validation = 0;

		buffer = _prompt(status);
		length = _get_length(buffer);
		_argv = (char **)malloc(sizeof(char *) * length);
		if (_argv == NULL)
		{
			perror("Unable to allocate argv");
			exit(1);
		}
		_init_argv(_argv, length);
		_get_argv(buffer, _argv, length);
		validation = _validate_argv(_argv, buffer);
		if (validation == 1)
			continue;
		if (validation == 2)
			exit(0);
		(counter)++;
		status = _execute_command(_argv, buffer, argv, &counter);
	}

	return (status);
}

/**
 * _execute_command - execute the command
 * @argv: the arguments
 * @buffer: the buffer
 * @_argv: the arguments
 * @counter: the counter
 * Return: 0 on success
 */
int _execute_command(char **argv, char *buffer, char **_argv, int *counter)
{
	char *command = NULL;
	int status = 0, not_exist = 0;
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

			results = _get_env_values("PATH=");
			command = _get_location(results, argv[0]);
			if (!command)
			{
				not_exist = 1;
				command = argv[0];
			}
		}
		else
			command = argv[0];
		_exec(command, argv, _argv, buffer, counter, not_exist);
		return (0);
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
 * _exec - execute the command
 * @command: the command
 * @argv: the arguments
 * @_argv: the arguments
 * @buffer: the buffer
 * @counter: the counter
 * @not_exist: if the command not exist
 */
void _exec(char *command, char **argv, char **_argv, char *buffer,
	   int *counter, int not_exist)
{
		if (_strcmp(command, "env") == 0)
			_print_env(argv, buffer);
		if (not_exist == 1)
		{
			_print_err(_argv, counter, command);
			exit(127);
		}
		if (execve(command, argv, environ) == -1)
			_print_err(_argv, counter, command);
		exit(127);
}

/**
 * _print_err - print the error
 * @argv: the arguments
 * @counter: the counter
 * @command: the command
 */
void _print_err(char **argv, int *counter, char *command)
{
	char err[1024] = "";
	char *counter_str = NULL;

	counter_str = _itoa(*counter);
	_strcpy(err, argv[0]);
	_strcat(err, ": ");
	_strcat(err, counter_str);
	_strcat(err, ": ");
	_strcat(err, command);
	_strcat(err, ": not found\n");
	write(STDERR_FILENO, err, _strlen(err));
	free(counter_str);
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
