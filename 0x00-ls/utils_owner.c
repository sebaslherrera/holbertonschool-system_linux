#include "ls.h"

char *get_owner(uid_t st_uid);

/**
 * get_owner - Owner of the given id
 * @st_uid: User id of owner
 * Return: string name of owner
 */
char *get_owner(uid_t st_uid)
{
	struct passwd *pass;

	pass = getpwuid(st_uid);

	if (pass == NULL)
		return (NULL);
	return (pass->pw_name);
}
