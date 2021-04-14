#include "ls.h"

void ls_simple(struct dirent *read, dlistint_t **head_files);
void ls_long_listing_format(struct dirent *read, char *input_path);

/**
 * main - Main function of ls project
 * @argc: Number of arguments - Integer
 * @argv: Array of arguments - Array of strings
 * Return: 0 on success, status codes on failure
 */
int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *read;
	char *input_path = NULL;
	dlistint_t *head_files = NULL;
	/* int flags = 0; */

	if (argc < 2)
		input_path = ".";
	else
		input_path = argv[1];
	/* printf("input_path: %s\n", input_path); */
	dir = opendir(input_path);
	if (dir == NULL)
	{
		fprintf(stderr, "%s: cannot access %s: No such file or directory\n",
				argv[0], argv[1]);
		return (-1);
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (argc <= 2)
		{
			ls_simple(read, &head_files);
		}
		else
		{
			/* printf("Executing ls_list_all()\n"); */
			ls_long_listing_format(read, input_path);
		}
	}

	print_simple(head_files);
	free_list(&head_files);

	closedir(dir);

	return (0);
}

/**
 * ls_simple - Simple format of ls
 * @read: Pointer of directory structure
 * @head_files: Head of doubly linked list that stores data files
 * Return: void
 */
void ls_simple(struct dirent *read, dlistint_t **head_files)
{
	if (_strcmp(read->d_name, ".") != 0 || _strcmp(read->d_name, ".") != 0)
		add_dnode(head_files, read->d_name);
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
