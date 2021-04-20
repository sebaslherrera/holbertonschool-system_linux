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
 * struct DListElmt_ - doubly linked list
 * @data: pointer of void
 * @prev: points to the previous node
 * @next: points to the next node
 *
 * Description: doubly linked list node structure
 * for Holberton project
 */
typedef struct DListElmt_
{
	void *data;
	struct DListElmt_ *prev;
	struct DListElmt_ *next;
} DListElmt;

/**
 * struct DList_ - doubly linked handler
 * @size: pointer of void
 * @match: points to the previous node
 * @destroy: points to the next node
 * @head: points to the next node
 * @tail: points to the next node
 *
 * Description: doubly linked list node structure
 * for Holberton project
 */
typedef struct DList_
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	DListElmt *head;
	DListElmt *tail;
} DList;

void ls_long_listing_format(struct dirent *read, char *input_path);
void add_dirs_list(struct dirent *read, DList *fd_of_dirs, char *flags);

void iterate_directories(DList *directories, DList *head_files,
						 int n_files, int n_directories, char *flags, DList *errors);

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

int check_owner_permission(char *path);

/* Dlist Library */
void dlist_init(DList *list, void (*destroy)(void *data));
void dlist_destroy(DList *list);
int dlist_ins_next(DList *list, DListElmt *element, const void *data);
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);
int dlist_remove(DList *list, DListElmt *element, void **data);
#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

/* Custom DList library */
void destroy(void *data);
size_t print_dlist(const DList *h);
size_t print_error_permission(const DList *h, int *exit_code);

#endif
