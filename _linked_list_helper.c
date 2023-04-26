#include "shell.h"
/**
 * add_node_end - adds a new node at the end of a list_s.
 * @head: linked list head.
 * @str: string.
 * Return: the address of the first node.
 */
list_s *add_node_end(list_s **head, const char *str)
{
	list_s *node = NULL;
	list_s *temp = NULL;

	node = malloc(sizeof(list_s));
	if (!node)
	{
		return (NULL);
	}
	node->str = _strdup(str);
	node->len = _strlen(str);
	node->next = NULL;
	if (!(*head))
	{
		(*head) = node;
		return (node);
	}

	temp = *head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = node;

	return (node);
}

/**
 * free_list - frees a list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_list(list_s *head)
{
	list_s *current_node = head;

	while (current_node != NULL)
	{
		head = head->next;
		free(current_node->str);
		free(current_node);
		current_node = head;
	}
}
