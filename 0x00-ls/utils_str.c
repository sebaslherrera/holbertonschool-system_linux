#include "ls.h"

int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strstr(char *haystack, char *needle);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);

/**
 * _strcmp - Compares two strings
 * @s1: Pointer to a char[]
 * @s2: Pointer to a char[]
 * Return: Integer value
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}

	return (0);
}

/**
 * _strlen - Length of the string
 *
 * @s: Pointer of char variable
 * Return: Integer value
 */
int _strlen(char *s)
{
	char *t;
	int counter = 0;

	for (t = s; *t != '\0'; t++)
		counter++;

	return (counter);
}

/**
 * *_strstr - locate a substring
 * @haystack: char pointer
 * @needle: char pointer
 *
 * Return: The substring associated
 */
char *_strstr(char *haystack, char *needle)
{

	while (*haystack != '\0')
	{
		char *i = haystack;
		char *j = needle;

		while (*j == *haystack && *j != '\0' && *haystack != '\0')
		{
			haystack++;
			j++;
		}
		if (*j == '\0')
			return (i);
		haystack = i + 1;
	}
	return (NULL);
}

/**
 * *_strcat - Concatenates two strings
 * @dest: String of destiny, pointer to a char[]
 * @src: Source string, pointer to a char[]
 * Return: Char[] concatenated
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; *dest != 0; i++)
		dest++;

	for (j = 0; src[j] != 0; j++)
	{
		*dest = src[j];
		dest++;
	}
	*dest = '\0';
	dest -= (i + j);
	return (dest);
}

/**
 * *_strdup - Function returns a pointer to a new string
 * which is a duplicate of the string str.
 * @str: String
 * Return: Pointer to a new string
 */
char *_strdup(char *str)
{
	char *dupli, *copy;
	int len = 0, i;

	if (str == NULL)
		return (NULL);

	for (copy = str; *copy != '\0'; copy++)
		len++;

	dupli = malloc(len + 1);
	if (dupli == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		*(dupli + i) = *(str + i);
	*(dupli + i) = '\0';
	return (dupli);
}
