#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of buffer.
 * @len: Address of len variable.
 *
 * Return: Number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it. */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline. */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			
			/* Check if the buffer contains a command chain. */
			if (_strchr(*buf, ';'))
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}

	return (r);
}

/**
 * get_input - Gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer. */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg);
	char *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF. */
		return (-1);

	if (len) /* We have commands left in the chain buffer. */
	{
		j = i; /* Initialize new iterator to current buffer position. */
		p = buf + i; /* Get pointer for return. */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to semicolon or end. */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';'. */
		if (i >= len) /* Reached end of buffer? */
		{
			i = len = 0; /* Reset position and length. */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position. */
		return (_strlen(p)); /* Return length of current command. */
	}

	*buf_p = buf; /* Else not a chain, pass back buffer from _getline(). */
	return (r); /* Return length of buffer from _getline(). */
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);

	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Number of bytes read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		r = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, r, r ? r + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (r)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	r += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = r;

	*ptr = p;
	return (r);
}

/**
 * sigintHandler - Handles SIGINT signal (Ctrl-C).
 * @sig_num: The signal number (unused).
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
