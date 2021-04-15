#include "ls.h"

void iterate_directories(dlistint_t *iter_derectories, dlistint_t *head_files,
						 int n_files, int n_directories);

void iterate_directories(dlistint_t *iter_derectories, dlistint_t *head_files,
						 int n_files, int n_directories)
{
	DIR *dir;
	struct dirent *read;
	(void)n_files;

	while (iter_derectories != NULL)
	{
		dir = opendir(iter_derectories->name);

		while ((read = readdir(dir)) != NULL)
		{
			ls_simple(read, &head_files);
		}
		if (n_directories >= 2 && iter_derectories->next != NULL)
		{
			printf("%s:\n", iter_derectories->name);
			print_simple(head_files);
			printf("\n");
		}
		else if (n_directories >= 2)
		{
			printf("%s:\n", iter_derectories->name);
			print_simple(head_files);
		}
		else
			print_simple(head_files);

		free_list(&head_files);
		iter_derectories = iter_derectories->next;
		closedir(dir);
	}
}
