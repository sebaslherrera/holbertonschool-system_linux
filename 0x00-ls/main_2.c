#include "ls.h"

/**
 * iterate_directories - Main function of ls project
 * @iter_derectories: Number of arguments - Integer
 * @fd_of_dirs: Array of arguments - Array of strings
 * @n_files: Array of arguments - Array of strings
 * @n_directories: Array of arguments - Array of strings
 * @flags: Array of arguments - Array of strings
 * Return: 0 on success, status codes on failure
 */
void iterate_directories(dlistint_t *iter_derectories, dlistint_t *fd_of_dirs,
						 int n_files, int n_directories, char *flags)
{
	DIR *dir;
	struct dirent *read;
	(void)n_files;

	while (iter_derectories != NULL)
	{
		dir = opendir(iter_derectories->name);

		while ((read = readdir(dir)) != NULL)
			add_dirs_list(read, &fd_of_dirs, flags);

		if ((n_files > 0 && n_directories > 0) || n_directories > 1)
		{
			printf("%s:\n", iter_derectories->name);
			print_simple(fd_of_dirs);
			if (iter_derectories->next != NULL)
				printf("\n");
		}
		else
			print_simple(fd_of_dirs);

		free_list(&fd_of_dirs);
		iter_derectories = iter_derectories->next;
		closedir(dir);
	}
}
