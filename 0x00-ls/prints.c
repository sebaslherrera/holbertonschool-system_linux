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
