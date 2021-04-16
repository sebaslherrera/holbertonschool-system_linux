#include "ls.h"

/**
 * read_content - Main function of ls project
 * @flags: Number of arguments - Integer
 * @dir: Number of arguments - Integer
 * @directories: Number of arguments - Integer
 * @n_files: Array of arguments - Array of strings
 * @n_directories: Array of arguments - Array of strings
 * @fd_of_dirs: Array of arguments - Array of strings
 * @errors: Array of arguments - Array of strings
 * Return: 0 on success, status codes on failure
 */
void read_content(char *flags, DIR *dir, dlistint_t *directories,
				  int n_files, int n_directories,
				  dlistint_t *fd_of_dirs, dlistint_t **errors)
{
	struct dirent *read;

	if (check_owner_permission(directories->name) == -1)
		add_dnode(errors, directories->name);
	else
	{
		while ((read = readdir(dir)) != NULL)
			add_dirs_list(read, &fd_of_dirs, flags);

		if ((n_files > 0 && n_directories > 0) || n_directories > 1)
		{
			printf("%s:\n", directories->name);
			print_simple(fd_of_dirs);
			if (directories->next != NULL)
				printf("\n");
		}
		else
			print_simple(fd_of_dirs);

		free_list(&fd_of_dirs);
	}
}

/**
 * iterate_directories - Main function of ls project
 * @directories: Number of arguments - Integer
 * @fd_of_dirs: Array of arguments - Array of strings
 * @n_files: Array of arguments - Array of strings
 * @n_directories: Array of arguments - Array of strings
 * @flags: Array of arguments - Array of strings
 * @errors: Array of arguments - Array of strings
 * Return: 0 on success, status codes on failure
 */
void iterate_directories(dlistint_t *directories, dlistint_t *fd_of_dirs,
						 int n_files, int n_directories, char *flags, dlistint_t **errors)
{
	DIR *dir;

	while (directories != NULL)
	{
		dir = opendir(directories->name);

		read_content(flags, dir, directories, n_files,
					 n_directories, fd_of_dirs, errors);

		print_dlistint(fd_of_dirs);

		free_list(&fd_of_dirs);
		directories = directories->next;
		closedir(dir);
	}
}
