#include "shell.h"

/**
 * _get_env - Gets an env variable.
 * @variable: The name of the environmental variable to get.
 *
 * Return: a pointer to the environmental variable otherwise
 *  NULL.
 */
char **_get_env(const char *variable)
{
	int i, length;

	length = _strlen(variable);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(variable, environ[i], length) == 0)
			return (&environ[i]);
	}

	return (NULL);
}

list_s *_get_env_values(const char *variable)
{
	char **env_value = _get_env(variable);
	char temp_env_value[1024];
	char *dirs = NULL;
	int index = 0;
	int equal_sign_index = 0;
	list_s *result = NULL;

	_strcpy(temp_env_value, *env_value);
	if (!env_value)
		return (NULL);

	while ((*env_value)[index] != '=')
		index++;
	equal_sign_index = ++index;

	dirs = _strtok((temp_env_value) + equal_sign_index, ":");
	while (dirs)
	{
		add_node_end(&result, dirs);
		dirs = _strtok(NULL, ":");
	}
	return (result);
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
