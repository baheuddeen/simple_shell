#include "shell.h"

/**
 * _prompt - prompt user to enter a command
 * Return: the buffer
 */
char *_prompt()
{
	char *buffer = NULL, *prompt = "$ ", *new_line = "\n";
	size_t bufsize = 256;
	size_t characters = 0;

	buffer = (char *)malloc(sizeof(char) * bufsize);
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
	}
	if (!isatty(STDIN_FILENO))
	{
		characters = _getline(&buffer, &bufsize, STDIN_FILENO);
		if (!characters)
			exit(0);
	}
	else
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		characters = _getline(&buffer, &bufsize, STDIN_FILENO);
	}

	if (feof(stdin))
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, new_line, _strlen(new_line));
		free(buffer);
		exit(0);
	}

	if (buffer[characters - 1] == '\n')
	{
		buffer[characters - 1] = '\0';
	}

	return (buffer);
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

/**
 * _getline - get the line
 * @buffer: the buffer
 * @bufsize: the buffer size
 * @fd: the file descriptor
 * Return: the length
 */
int _getline(char **buffer, size_t *bufsize, int fd)
{
	size_t i = 0;
	char c;

	while (read(fd, &c, 1) > 0)
	{
		if (i >= *bufsize)
		{
			*buffer = _realloc(*buffer, *bufsize, *bufsize + 256);
			if (*buffer == NULL)
			{
				perror("Unable to reallocate buffer");
				exit(1);
			}
		}
		(*buffer)[i] = c;
		i++;
		if (c == '\n')
			break;
	}
	(*buffer)[i] = '\0';
	return (i);
}
