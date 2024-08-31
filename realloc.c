#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: Byte to fill *s with.
 * @n: Number of bytes to be filled.
 *
 * Return: Pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees an array of strings.
 * @pp: Array of strings (terminated by NULL).
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: Size of the previous block.
 * @new_size: Size of the new block.
 *
 * Return: Pointer to the newly allocated block, or NULL if allocation fails.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int i;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		p[i] = ((char *)ptr)[i];

	free(ptr);
	return (p);
}
