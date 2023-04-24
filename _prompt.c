#include "shell.h"


/**
 * _prompt - prompt user to enter a command
 * @flag_exit: flag to exit
 * Return: the buffer
 */
char *_prompt(int *flag_exit)
{
	char *buffer = NULL;
	size_t bufsize = 256;
	size_t characters = 0;

	buffer = (char *)malloc(sizeof(char) * bufsize);
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
	}

	if (!isatty(STDIN_FILENO))
	{
		characters = getline(&buffer, &bufsize, stdin);
		*flag_exit = 1;
	}
	else
	{
		printf("$ ");
		characters = getline(&buffer, &bufsize, stdin);
	}

	if (feof(stdin))
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		free(buffer);
		exit(1);
	}

	if (buffer[characters - 1] == '\n')
	{
		buffer[characters - 1] = '\0';
	}

	return (buffer);
	return (0);
}

/**
 * _get_length - get the length of the buffer words
 * @buffer: the buffer
 * Return: the length
 */
int _get_length(char *buffer)
{
	int i = 0, length = 1;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == ' ')
			length++;
		i++;
	}
	length++;
	return (length);
}
