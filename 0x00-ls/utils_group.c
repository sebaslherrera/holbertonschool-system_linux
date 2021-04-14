#include "ls.h"

char *get_group(gid_t st_gid);

/**
 * get_group - Group owner of the given id
 * @st_gid: Group id of owner
 * Return: string name of group owner
 */
char *get_group(gid_t st_gid)
{
	struct group *grp;

	grp = getgrgid(st_gid);

	if (grp == NULL)
		return (NULL);
	return (grp->gr_name);
}
