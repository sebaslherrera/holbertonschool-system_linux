#include "ls.h"

void ls_long_listing_format(struct dirent *read, char *input_path);
char *check_flags(int argc, char **argv);

/**
 * check_file_or_directory - Main function of ls project
 * @path: Number of arguments - Integer
 * Return: 0 on success, status codes on failure
 */
int check_file_or_directory(char *path)
{
	struct stat st;
	char type = -1;

	/* Error */
	if (lstat(path, &st) == -1)
		return (type);

	switch (st.st_mode & S_IFMT)
	{
	case S_IFREG: /* Regular or ordinary file */
		type = 1;
		break;
	case S_IFDIR: /* Directory */
		type = 2;
		break;
	default: /* Other cases */
		type = -1;
		break;
	}

	return (type);
}

/**
 * file_or_directory - Main function of ls project
 * @argc: Number of arguments - Integer
 * @argv: Array of arguments - Array of strings
 * @flags: Array of arguments - Array of strings
 * @files: Array of arguments - Array of strings
 * @directories: Array of arguments - Array of strings
 * @n_dirs: Array of arguments - Array of strings
 * @n_files: Array of arguments - Array of strings
 * @ex_code: Exit code
 * Return: 0 on success, status codes on failure
 */
void file_or_directory(int argc, char **argv, char *flags, dlistint_t **files,
					   dlistint_t **directories, int *n_dirs, int *n_files, int *ex_code)
{
	int i, start = 1, status_file_or_dir = -1;

	if (argc == 1)
	{
		add_dnode(directories, ".");
		(*n_dirs)++;
		return;
	}

	if (flags != NULL && _strlen(flags) > 0)
		start = 2;

	for (i = start; argv[i] != NULL; i++)
	{
		status_file_or_dir = check_file_or_directory(argv[i]);
		/* printf("argv[%d]: %s\n", i, argv[i]); */
		if (status_file_or_dir == 1)
		{
			add_dnode(files, argv[i]);
			(*n_files)++;
		}
		else if (status_file_or_dir == 2)
		{
			add_dnode(directories, argv[i]);
			(*n_dirs)++;
		}
		else
			fprintf(stderr, "hls: cannot access %s: No such file or directory\n",
					argv[i]),
				*ex_code = 2;
	}
}

/**
 * check_flags - Main function of ls project
 * @argc: Number of arguments - Integer
 * @argv: Array of arguments - Array of strings
 * Return: 0 on success, status codes on failure
 */
char *check_flags(int argc, char **argv)
{
	char *all_flags = "1aAl", *flags_temp = NULL;
	int i, j, k = 0;

	/* Case without options */
	if (argc == 1)
		return (NULL);

	/* Case with -- */
	if (argc == 2 && argv[1][0] == '-' && _strcmp(argv[1], "--") == 0)
		return (NULL);
	flags_temp = malloc(sizeof(char) * 10);

	if (flags_temp == NULL)
		return (NULL);

	for (i = 0; argv[1][i] != '\0'; i++)
	{
		if (argv[1][0] == '-')
		{
			for (j = 0; all_flags[j] != '\0'; j++)
			{
				if (argv[1][i] == all_flags[j])
				{
					flags_temp[k] = all_flags[j];
					k++;
				}
			}
		}
	}
	flags_temp[k] = '\0';
	return (flags_temp);
}

/**
 * main - Main function of ls project
 * @argc: Number of arguments - Integer
 * @argv: Array of arguments - Array of strings
 * Return: 0 on success, status codes on failure
 */
int main(int argc, char **argv)
{
	dlistint_t *fd_of_dirs = NULL, *files = NULL,
			   *directories = NULL, *iter_derectories = NULL;
	char *flags = NULL;
	int n_directories = 0, n_files = 0, exit_code = 0;

	flags = check_flags(argc, argv);
	file_or_directory(argc, argv, flags, &files,
					  &directories, &n_directories, &n_files, &exit_code);

	print_simple(files);
	if (n_files > 0 && n_directories > 0)
		printf("\n");

	iter_derectories = directories;

	iterate_directories(iter_derectories, fd_of_dirs,
						n_files, n_directories, flags);

	free_list(&files);
	free_list(&directories);
	free(flags);

	return (exit_code);
}

/**
 * add_dirs_list - Simple format of ls
 * @read: Pointer of directory structure
 * @fd_of_dirs: Head of doubly linked list that stores data files
 * @flags: Head of doubly linked list that stores data files
 * Return: void
 */
void add_dirs_list(struct dirent *read, dlistint_t **fd_of_dirs, char *flags)
{
	/* Basic case no flags*/
	if (flags == NULL || _strlen(flags) == 0)
	{
		if (read->d_name[0] != '.')
			add_dnode(fd_of_dirs, read->d_name);
		return;
	}
}

/**
 * ls_long_listing_format - List format of ls
 * @read: Pointer of directory structure
 * @input_path: path of directory opened
 * Return: void
 */
void ls_long_listing_format(struct dirent *read, char *input_path)
{
	struct stat buf;
	char *protection = NULL, *datetime = NULL, *owner = NULL, *group = NULL;

	(void)input_path;

	lstat(read->d_name, &buf);

	protection = get_permissions(buf.st_mode);
	owner = get_owner(buf.st_uid);
	group = get_group(buf.st_gid);
	datetime = get_datetime(buf.st_mtime);
	printf("%s %lu %s %s %5ld %s %s\n",
		   protection, buf.st_nlink, owner, group,
		   buf.st_size, datetime, read->d_name);
	free(protection);
	free(datetime);
}
