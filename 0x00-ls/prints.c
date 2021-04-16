#include "ls.h"

/**
 * print_simple - Prints all the elements of a double linked list
 * @h: Head of the linked list
 *
 * Return: Number of nodes (size_t)
 */
size_t print_simple(const dlistint_t *h)
{
	size_t i = 0;

	while (h != NULL)
	{
		if (h->next == NULL)
			printf("%s\n", h->name);
		else
			printf("%s  ", h->name);

		h = h->next;
		i++;
	}

	return (i);
}

/**
 * print_error_permission - Prints all the elements of a double linked list
 * @h: Head of the linked list
 * @exit_code: Integer exit code
 *
 * Return: Number of nodes (size_t)
 */
size_t print_error_permission(const dlistint_t *h, int *exit_code)
{
	size_t i = 0;

	while (h != NULL)
	{
		fprintf(stderr, "hls: cannot open directory %s: Permission denied\n",
				h->name);

		h = h->next;
		i++;
		*exit_code = 2;
	}

	return (i);
}
