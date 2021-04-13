#include "ls.h"

char *get_permissions(unsigned int st_mode);
char *get_type_of_file(unsigned int st_mode, char *permissions);
char *get_rights_of_file(unsigned int st_mode, char *permissions);

char *get_permissions(unsigned int st_mode)
{
    char *permissions = NULL;
    int size = 11, i = 0;

    permissions = malloc(sizeof(char) * size); /* Heap */
    if (permissions == NULL)
        return (NULL);

    for (i = 0; i < size - 1; i++)
        permissions[i] = '-';
    permissions[size - 1] = '\0';

    get_type_of_file(st_mode, permissions);
    get_rights_of_file(st_mode, permissions);
    return (permissions);
}

char *get_type_of_file(unsigned int st_mode, char *permissions)
{
    switch (st_mode & S_IFMT)
    {
    case S_IFREG: /* Regular or ordinary file */
        permissions[0] = '-';
    case S_IFDIR: /* Directory */
        permissions[0] = 'd';
        break;
    case S_IFLNK: /* Symbolic link */
        permissions[0] = 'l';
        break;
    case S_IFBLK: /* Block device */
        permissions[0] = 'b';
        break;
    case S_IFIFO: /* Named pipe file */
        permissions[0] = 'p';
        break;
    case S_IFCHR: /* Character special file */
        permissions[0] = 'c';
        break;
    case S_IFSOCK: /* Socket */
        permissions[0] = 's';
        break;
    default: /* Other cases */
        permissions[0] = '-';
        break;
    }
    return (permissions);
}

char *get_rights_of_file(unsigned int st_mode, char *permissions)
{
    /* Owner permissions */
    if (st_mode & S_IRUSR)
        permissions[1] = 'r';
    if (st_mode & S_IWUSR)
        permissions[2] = 'w';
    if (st_mode & S_IXUSR)
        permissions[3] = 'x';

    /* Group permissions */
    if (st_mode & S_IRGRP)
        permissions[4] = 'r';
    if (st_mode & S_IWGRP)
        permissions[5] = 'w';
    if (st_mode & S_IXGRP)
        permissions[6] = 'x';

    /* Others permissions */
    if (st_mode & S_IROTH)
        permissions[7] = 'r';
    if (st_mode & S_IWOTH)
        permissions[8] = 'w';
    if (st_mode & S_IXOTH)
        permissions[9] = 'x';

    return (permissions);
}
