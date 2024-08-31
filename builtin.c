#include "shell.h"

/**
 * _myexit - Exits the shell with a given status.
 * @info: Pointer to the structure containing potential arguments.
 *         Used to maintain a constant function prototype.
 *
 * Return: Exits with the given exit status.
 *         Returns 0 if `info.argv[0]` is not "exit".
 */
int _myexit(info_t *info)
{
	int exit_status;

	if (info->argv[1])  /* Check if there is an exit argument */
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_status;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current directory of the process.
 * @info: Pointer to the structure containing potential arguments.
 *         Used to maintain a constant function prototype.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_status;

	current_dir = getcwd(buffer, sizeof(buffer));
	if (!current_dir)
		_puts("Error: Unable to get current directory\n");

	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			target_dir = _getenv(info, "PWD=");
		chdir_status = chdir(target_dir ? target_dir : "/");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		target_dir = _getenv(info, "OLDPWD=");
		if (!target_dir)
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(target_dir);
		_putchar('\n');
		chdir_status = chdir(target_dir);
	}
	else
	{
		chdir_status = chdir(info->argv[1]);
	}

	if (chdir_status == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}

	return (0);
}

/**
 * _myhelp - Provides help information for shell commands.
 * @info: Pointer to the structure containing potential arguments.
 *         Used to maintain a constant function prototype.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	char **arg_array = info->argv;

	_puts("Help command executed. Functionality not yet implemented.\n");
	if (0)
		_puts(*arg_array); /* Temporary workaround for unused variable warning */

	return (0);
}
