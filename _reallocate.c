#include "shell.h"

/**
 * _realloc - reallocate memory
 * @ptr: the pointer
 * @new_size: the new size
 * Return: the pointer
 */
void *_realloc(void *ptr, unsigned new_size)
{
	char *new_ptr;
	unsigned i = 0;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	while (i < new_size && ((char *)ptr)[i] != '\0')
	{
		new_ptr[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}
