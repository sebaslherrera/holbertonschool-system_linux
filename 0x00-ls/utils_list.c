#include "ls.h"

dlistint_t *add_dnode(dlistint_t **head, char *name);
void free_list(dlistint_t **head);
size_t print_dlistint(const dlistint_t *h);

/**
 * add_dnode - Add a node in the head of the list
 * @head: Memory of the Head of the linked list
 * @n: Integer data
 *
 * Return: Head of the list
 */
dlistint_t *add_dnode(dlistint_t **head, char *name)
{
	dlistint_t *new = malloc(sizeof(dlistint_t));

	if (head == NULL || new == NULL)
		return (NULL);

	new->name = _strdup(name);
	new->prev = NULL;
	new->next = NULL;

	if (*head != NULL)
	{
		new->next = *head;
		(*head)->prev = new;
	}

	*head = new;

	return (*head);
}

/**
 * free_list - Free the list and put NULL in the head
 * @head: Head of the list
 *
 * Return: nothing
 */
void free_list(dlistint_t **head)
{
	dlistint_t *temp;

	if (head == NULL)
		return;

	while (*head != NULL)
	{
		temp = *head;
		*head = temp->next;
		free(temp->name);
		free(temp);
	}
	*head = NULL;
}

/**
 * print_dlistint - Prints all the elements of a double linked list
 * @h: Head of the linked list
 *
 * Return: Number of nodes (size_t)
 */
size_t print_dlistint(const dlistint_t *h)
{
	size_t i = 0;

	while (h != NULL)
	{
		printf("%s ", h->name);
		h = h->next;
		i++;
	}

	return (i);
}