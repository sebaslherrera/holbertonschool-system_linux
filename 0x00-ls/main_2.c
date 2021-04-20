#include "ls.h"

/**
 * read_content - Main function of ls project
 * @flags: Number of arguments - Integer
 * @dir: Number of arguments - Integer
 * @dir_head: Number of arguments - Integer
 * @n_files: Array of arguments - Array of strings
 * @n_directories: Array of arguments - Array of strings
 * @fd_of_dirs: Array of arguments - Array of strings
 * @errors: Array of arguments - Array of strings
 * Return: 0 on success, status codes on failure
 */
void read_content(char *flags, DIR *dir, DListElmt *dir_head,
				  int n_files, int n_directories,
				  DList *fd_of_dirs, DList *errors)
{
	struct dirent *read;

	if (check_owner_permission(dlist_data(dir_head)) == -1)
		dlist_ins_next(errors, errors->tail, dlist_data(dir_head));
	else
	{
		while ((read = readdir(dir)) != NULL)
			add_dirs_list(read, fd_of_dirs, flags);

		if ((n_files > 0 && n_directories > 0) || n_directories > 1)
		{
			printf("%s:\n", (char *)dlist_data(dir_head));
			print_dlist(fd_of_dirs);
			if (dlist_next(dir_head) != NULL)
				printf("\n");
		}
		else
			print_dlist(fd_of_dirs);

		dlist_destroy(fd_of_dirs);
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
void iterate_directories(DList *directories, DList *fd_of_dirs,
						 int n_files, int n_directories, char *flags, DList *errors)
{
	DIR *dir;
	DListElmt *dir_head = dlist_head(directories);

	while (dir_head != NULL)
	{
		dir = opendir(dlist_data(dir_head));

		read_content(flags, dir, dir_head, n_files,
					 n_directories, fd_of_dirs, errors);

		dir_head = dlist_next(dir_head);
		closedir(dir);
	}
}
