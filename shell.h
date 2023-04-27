#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 */

typedef struct list_s
{
	char *str;
	int len;
	struct list_s *next;
} list_s;

void sig_handler(int sig);
char *_prompt(int status);
int _getline(char **buffer, size_t *bufsize, int fd);
char *_strtok(char *str, const char *delim);
char *_strpbrk(char *s, const char *accept);
char *_strchr(const char *s, int c);
char *_strdup(const char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _print_argv(char **argv);
int _get_length(char *buffer);
void _init_argv(char **argv, int length);
void _get_argv(char *buffer, char **argv, int length);
int _validate_argv(char **argv, char *buffer);
void _print_env(char **argv, char *buffer);
int _execute_command(char **argv, char *buffer, char **_argv, int *counter);
list_s *_get_env_values(const char *variable);
char *_get_location(list_s *dirs, char *command);
void _print_err(char **argv, int *counter, char *command);
char *_itoa(int num);
void _exec(char *command, char **argv, char **_argv, char *buffer,
		   int *counter, int not_exist);

/** Linked List*/
void free_list(list_s *head);
list_s *add_node_end(list_s **head, const char *str);
size_t print_list(const list_s *h);

#endif
