#include "shell.h"

/**
 * _strncpy - Copies a string up to a specified number of characters.
 * @dest: The destination buffer.
 * @src: The source string.
 * @n: The number of characters to copy.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
	{
		dest[i] = src[i];
	}
	if (i < n)
	{
		for (j = i; j < n; j++)
		{
			dest[j] = '\0';
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings up to a specified number of characters.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of bytes to use from the source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[i] = src[j];
		i++;
	}
	if (j < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 *
 * Return: Pointer to the 1st occurrence of character, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (NULL);
}
