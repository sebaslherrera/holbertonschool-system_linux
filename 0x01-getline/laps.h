#ifndef LAPS_H
#define LAPS_H

#include <stdlib.h>
#include <stdio.h>

/**
 * struct ListElmt_ - single linked list
 * @data: pointer of void
 * @next: points to the next node
 *
 * Description: doubly linked list node structure
 * for Holberton project
 */
typedef struct ListElmt_
{
	void *data;
	struct ListElmt_ *next;
} ListElmt;

/**
 * struct Data_ - Struct that represent the car data
 * @id: Unique id of the car
 * @laps: Current lap of the car
 *
 */
typedef struct Data_
{
	int id;
	size_t laps;
} Data;

void add_car(int id, ListElmt **head);
void race_state(int *id, size_t size);

#endif /* LAPS_H */
