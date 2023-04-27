#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * _get_argv - get the arguments from the buffer
 * @buffer: the buffer
 * @argv: the arguments
 * @length: length of the buffer words
 */
void _get_argv(char *buffer, char **argv, int length)
{
	int i = 0;
	char *token = _strtok(buffer, " ");

	while (token != NULL && i < length)
	{
		if (_strcmp(token, " ") == 0 || _strcmp(token, "\t") == 0)
		{
			token = _strtok(NULL, " ");
			continue;
		}
		argv[i] = token;
		token = _strtok(NULL, " ");
		i++;
	}
}

/**
 * _print_argv - print the arguments
 * @argv: the arguments
 * Return: 0
 */
int _print_argv(char **argv)
{
	int i = 0;

	while (argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (0);
}

/**
 * _init_argv - initialize the arguments
 * @argv: the arguments
 * @length: the length of the buffer characters
 */
void _init_argv(char **argv, int length)
{
	int i = 0;

	while (i < length)
	{
		argv[i] = NULL;
		i++;
	}
}

/**
 * _validate_argv - validate the arguments
 * @argv: the arguments
 * @buffer: the buffer
 * Return: 0 on success
 */
int _validate_argv(char **argv, char *buffer)
{
	if (argv[0] == NULL)
	{
		free(argv);
		free(buffer);
		return (1);
	}
	if (_strcmp(argv[0], "exit") == 0)
	{
		free(argv);
		free(buffer);
		return (2);
	}
	return (0);
}
