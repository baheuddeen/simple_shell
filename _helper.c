#include "shell.h"


/**
 * number_length - Counts the digit length of a number.
 * @num: The number to count.
 *
 * Return: The digit length.
 */
int number_length(int num)
{
	unsigned int number;
	int len = 1;

	if (num < 0)
	{
		len++;
		number = num * -1;
	}
	else
	{
		number = num;
	}
	while (number > 9)
	{
		len++;
		number /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 * Return: The string as a buffer.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = number_length(num);
	unsigned int number;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		number = num * -1;
		buffer[0] = '-';
	}
	else
	{
		number = num;
	}

	len--;
	do {
		buffer[len] = (number % 10) + '0';
		number /= 10;
		len--;
	} while (number > 0);

	return (buffer);
}
