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

/**
 * struct dlistint_s - doubly linked list
 * @n: integer
 * @prev: points to the previous node
 * @next: points to the next node
 *
 * Description: doubly linked list node structure
 * for Holberton project
 */
typedef struct dlistint_s
{
	char *name;
	struct dlistint_s *prev;
	struct dlistint_s *next;
} dlistint_t;

void ls_long_listing_format(struct dirent *read, char *input_path);
void ls_simple(struct dirent *read, dlistint_t **head_files);

/* Prints based on lists */
size_t print_simple(const dlistint_t *h);

/* Files long list information */
char *get_permissions(unsigned int st_mode);
char *get_type_of_file(unsigned int st_mode, char *permissions);
char *get_rights_of_file(unsigned int st_mode, char *permissions);
char *get_datetime(time_t mtime);
char *get_owner(uid_t st_uid);
char *get_group(gid_t st_gid);

/* String library */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strstr(char *haystack, char *needle);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);

/* Doubly Linked List library */
dlistint_t *add_dnode(dlistint_t **head, char *name);
void free_list(dlistint_t **head);
size_t print_dlistint(const dlistint_t *h);

#endif
