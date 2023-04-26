#include "shell.h"
#include <stdlib.h>

/**
 * _strtok - tokenize a string
 * @str: the string to tokenize
 * @delim: the delimiter string
 * Return: a pointer to the next token, or NULL if there are no more tokens.
 */
char *_strtok(char *str, const char *delim)
{
	static char *src;

	char *p, *ret = 0;

	if (str != NULL)
		src = str;

	if (src == NULL)
		return (NULL);

	p = _strpbrk(src, delim);
	if (p != NULL)
	{
		*p = 0;
		ret = src;
		src = ++p;
	}
	else if (*src)
	{
		ret = src;
		src = NULL;
	}

	return (ret);
}

/**
 * _strpbrk - find the first occurrence in s of any character in accept
 * @s: the string to search
 * @accept: the characters to search for
 * Return: a pointer to the character in s that matches one of the characters
 * in accept, or NULL if no such character is found.
 */
char *_strpbrk(char *s, const char *accept)
{
	while (*s)
	{
		if (_strchr(accept, *s))
			return (s);
		s++;
	}
	return (NULL);
}

/**
 * _strchr - locate a character in a string
 * @s: the string to search
 * @c: the character to search for
 * Return: a pointer to the first occurrence of c in s,
 * or NULL if c is not found.
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/**
 * _strdup - duplicate a string
 * @str: the string to duplicate
 * Return: a pointer to the duplicated string, or NULL if insufficient memory
 * was available.
 */
char *_strdup(const char *str)
{
	char *dup;
	int len = _strlen(str);

	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	_strcpy(dup, str);
	return (dup);
}

/**
 * _strlen - find the length of a string
 * @s: the string to find the length of
 * Return: the length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (*s++)
		len++;

	return (len);
}
