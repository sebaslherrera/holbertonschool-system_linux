#include "laps.h"

void add_node(int id, ListElmt **head, int to_head);
void free_all(ListElmt **head);

/**
 * race_state - function that keeps track of the number of laps
 * made by several cars in a race.
 * @id: is an array of int representing the “identifier” of each car.
 * @size: is the size of this array
 *
 */
void race_state(int *id, size_t size)
{
	static ListElmt *list_head;
	ListElmt *temp_car;
	size_t i;

	if (size == 0)
		free_all(&list_head);

	for (i = 0; i < size; i++)
		add_car(id[i], &list_head);

	printf("Race state:\n");
	for (temp_car = list_head; temp_car != NULL; temp_car = temp_car->next)
		printf("Car %d [%lu laps]\n", ((Data *)temp_car->data)->id,
			   ((Data *)temp_car->data)->laps);
}

/**
 * add_car - Add a car to a linked list.
 * @id: unique id of the new car.
 * @head: Pointer to the head of the linked list
 *
 */
void add_car(int id, ListElmt **head)
{
	ListElmt *temp_head = NULL;

	if (head == NULL || *head == NULL || ((Data *)(*head)->data)->id > id)
		add_node(id, head, 1);
	else
	{
		temp_head = *head;

		while (temp_head->next != NULL && ((Data *)temp_head->next->data)->id <= id)
			temp_head = temp_head->next;

		if (((Data *)temp_head->data)->id == id)
		{
			((Data *)temp_head->data)->laps += 1;
			return;
		}

		add_node(id, &temp_head, 0);
	}
}

/**
 * add_node - Add node to a single linked list to head or not.
 * @id: unique id of the new car.
 * @head: Pointer to the head of the linked list
 * @to_head: flag to identify where to insert the node
 *
 */
void add_node(int id, ListElmt **head, int to_head)
{
	ListElmt *new_car = NULL;
	Data *data = NULL;

	new_car = malloc(sizeof(ListElmt));
	data = malloc(sizeof(Data));

	if (new_car == NULL || data == NULL)
		return;

	data->id = id;
	data->laps = 0;
	new_car->data = data;

	if (to_head)
	{
		new_car->next = *head;
		*head = new_car;
	}
	else
	{
		new_car->next = (*head)->next;
		(*head)->next = new_car;
	}
	printf("Car %d joined the race\n", id);
}

/**
 * free_all - Free all memory of data struct and list struct
 * @head: Pointer to the head of the linked list
 *
 */
void free_all(ListElmt **head)
{
	ListElmt *temp = NULL;

	while (*head != NULL)
	{
		temp = *head;
		(*head) = (*head)->next;
		free(temp->data);
		free(temp);
	}
	exit(EXIT_SUCCESS);
}
