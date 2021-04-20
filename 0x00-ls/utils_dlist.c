#include "ls.h"

/**
 * destroy - Prints all the elements of a double linked list
 * @data: Head of the linked list
 *
 * Return: Number of nodes (size_t)
 */
void destroy(void *data)
{
	(void)data;
}

/**
 * print_dlist - Prints all the elements of a double linked list
 * @list: Head of the linked list
 *
 * Return: Number of nodes (size_t)
 */
size_t print_dlist(const DList *list)
{
	size_t i = 0;
	DListElmt *tail = list->tail;

	while (tail != NULL)
	{
		if (tail->prev == NULL)
			printf("%s\n", (char *)tail->data);
		else
			printf("%s  ", (char *)tail->data);
		tail = tail->prev;
		i++;
	}

	return (i);
}

/**
 * print_error_permission - Prints all the elements of a double linked list
 * @list: Head of the linked list
 * @exit_code: Integer exit code
 *
 * Return: Number of nodes (size_t)
 */
size_t print_error_permission(const DList *list, int *exit_code)
{
	size_t i = 0;

	DListElmt *tail = list->tail;

	while (tail != NULL)
	{
		fprintf(stderr, "hls: cannot open directory %s: Permission denied\n",
				(char *)tail->data);

		tail = tail->prev;
		i++;
		*exit_code = 2;
	}

	return (i);
}
