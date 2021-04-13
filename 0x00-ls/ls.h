#ifndef LS_H
#define LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

void ls_long_listing_format(struct dirent *read, char *input_path);

char *get_permissions(unsigned int st_mode);
char *get_type_of_file(unsigned int st_mode, char *permissions);
char *get_rights_of_file(unsigned int st_mode, char *permissions);

char *get_datetime(time_t mtime);

char *get_owner(uid_t st_uid);

char *get_group(gid_t st_gid);

#endif
