#include "ls.h"

int main(int argc, char **argv);
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
		printf("%s: cannot access %s: No such file or directory\n",
			   argv[0], argv[1]);
		return (-1);
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (argc < 2)
		{
			printf("Pase por aqui\n");
			printf("%s\n", read->d_name);
		}
		else
		{
			/* printf("Executing ls_list_all()\n"); */
			ls_long_listing_format(read, input_path);
		}
	}

	closedir(dir);

	return (0);
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
	printf("%s %lu %s %s %ld %s %s\n",
		   protection, buf.st_nlink, owner, group,
		   buf.st_size, datetime, read->d_name);
	free(protection);
	free(datetime);
}
