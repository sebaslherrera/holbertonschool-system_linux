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

/**
 * check_owner_permission - Main function of ls project
 * @path: Number of arguments - Integer
 * Return: 0 on success, status codes on failure
 */
int check_owner_permission(char *path)
{
	struct stat st;

	/* Error */
	if (lstat(path, &st) == -1)
		return (-1);

	if (st.st_mode & S_IRUSR)
		return (0);

	return (-1);
}
