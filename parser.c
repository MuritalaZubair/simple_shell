#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct (unused in this function).
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info; /* Unused parameter */
	if (!path || stat(path, &st))
		return (0);

	return (st.st_mode & S_IFREG);
}

/**
 * dup_chars - Duplicates characters from a string, excluding ':'.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a newly allocated buffer with the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	char *buf;
	int i, k;

	if (start >= stop)
		return (NULL);

	buf = malloc(sizeof(char) * (stop - start + 1));
	if (!buf)
		return (NULL);

	for (i = start, k = 0; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = '\0'; /* Ensure null termination */
	return (buf);
}

/**
 * find_path - Finds a command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, NULL otherwise.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;
	
	if (!pathstr || !cmd)
		return (NULL);

	/* Check for relative paths */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (pathstr[i])
	{
		if (pathstr[i] == ':' || !pathstr[i + 1])
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (path)
			{
				if (*path)
					_strcat(path, "/");
				_strcat(path, cmd);
				if (is_cmd(info, path))
					return (path);
				free(path); /* Free memory if not used */
			}
			curr_pos = i + 1;
		}
		i++;
	}

	return (NULL);
}
