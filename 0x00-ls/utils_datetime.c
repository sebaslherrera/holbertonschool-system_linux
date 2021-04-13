#include "ls.h"

char *get_datetime(time_t mtime);

char *get_datetime(time_t mtime)
{
	char *datetime = NULL, *format_date = NULL;
	int size = 13, i = 0;

	datetime = ctime(&(mtime));
	format_date = malloc(sizeof(char) * size); /* Heap */

	for (i = 0; i < size - 1; i++)
		format_date[i] = datetime[i + 4];

	format_date[size - 1] = '\0'; /* End string */

	return (format_date);
}
