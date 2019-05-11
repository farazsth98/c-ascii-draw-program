/* 	This linked_list.c file has been adapted from the linked list that
 *	we were required to implement in prac 7. A lot of the functions have
 *	been omitted as they were not required, and the linked list has primarily
 *	been turned into a linked list that stores a char *, instead of a void *
 *
 *	FILE:	linked_list.c
 *	AUTHOR:	Syed Faraz Abrar (19126296)
 *	UNIT:	COMP1000
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/* 	This function inserts a node with the imported char * as its data
 *	at the end of the linked list
 */
void insertLast(Node **head, char *str)
{
	Node *current = *head;
	Node *node = (Node *) malloc(sizeof(Node));
	strcpy(node->str, str);
	node->next = NULL;
	
	if (*head == NULL)
	{
		*head = node;
	}
	else if (current->next != NULL)
	{
		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = node;
	}
	else
	{
		current->next = node;
	}

	if(*head == NULL) printf("WTF\n");
}


/* This function is used to free the entire linked list recursively */
void freeList(Node **head)
{
	if (*head != NULL)
	{
		freeList(&((*head)->next));

		free(*head);
	}
}


