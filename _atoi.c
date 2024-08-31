#include "shell.h"

/**
* interactive - Checks if the shell is running in interactive mode.
* @info: Pointer to the struct containing the shell information.
*
* Return: 1 if in interactive mode, 0 otherwise.
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim - Determines if a character is a delimiter.
* @c: The character to check.
* @delim: The string containing delimiter characters.
*
* Return: 1 if the character is a delimiter, 0 otherwise.
*/
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
* _isalpha - Checks if a character is an alphabetic character.
* @c: The character to check.
*
* Return: 1 if the character is alphabetic, 0 otherwise.
*/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/**
* _atoi - Converts a string to an integer.
* @s: The string to be converted.
*
* Return: The converted integer, or 0 if no valid conversion is found.
*/
int _atoi(char *s)
{
	int i = 0, sign = 1, flag = 0;

	unsigned int result = 0;

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result = (result * 10) + (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
		i++;
	}
	if (sign == -1)
		return (-result);
	else
		return (result);
}
