#include "shell.h"

/**
 * _get_env - Gets an env variable.
 * @variable: The name of the environmental variable to get.
 *
 * Return: a pointer to the environmental variable other wise
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
	char *dirs = NULL;
	int index = 0;
	int equal_sign_index = 0;
	list_s *result = NULL;

	if (!env_value)
		return (NULL);

	while ((*env_value)[index] != '=')
		index++;
	equal_sign_index = ++index;

	dirs = _strtok((*env_value) + equal_sign_index, ":");
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
