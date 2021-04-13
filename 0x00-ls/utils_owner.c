#include "ls.h"

char *get_owner(uid_t st_uid);

char *get_owner(uid_t st_uid)
{
	struct passwd *pass;

	pass = getpwuid(st_uid);

	if (pass == NULL)
		return (NULL);
	return (pass->pw_name);
}
