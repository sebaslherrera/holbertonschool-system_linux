#include "ls.h"

void ls_simple(struct dirent *read, dlistint_t **head_files);
void ls_long_listing_format(struct dirent *read, char *input_path);

/**
 * main - opendir(), readdir(), closedir() exercises
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *read; /* Struct used by readdir */
	char *input_path = NULL;
	dlistint_t *head_files = NULL;
	/* int flags = 0; */

	printf("argc: %d\n", argc);

	if (argc < 2)
	{
		printf("No input\n");
		return (-1);
	}
	input_path = argv[1];
	printf("input_path: %s\n", input_path);
	dir = opendir(input_path);
	if (dir == NULL)
	{
		fprintf(stderr, "%s: cannot access %s: No such file or directory\n",
				argv[0], argv[1]);
		return (-1);
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (argc == 2)
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

void ls_simple(struct dirent *read, dlistint_t **head_files)
{
	add_dnode(head_files, read->d_name);
}

void ls_long_listing_format(struct dirent *read, char *input_path)
{
	struct stat buf; /* Buffer of lstat */
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
