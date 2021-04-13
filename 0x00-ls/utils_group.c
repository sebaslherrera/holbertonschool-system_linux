#include "ls.h"

char *get_group(gid_t st_gid);

char *get_group(gid_t st_gid)
{
	struct group *grp;

	grp = getgrgid(st_gid);

	if (grp == NULL)
		return (NULL);
	return (grp->gr_name);
}
