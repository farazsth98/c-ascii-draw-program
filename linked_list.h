/* This linked_list.h file has been adapted from 
 * prac 7, where we were asked to implement our own linked list.
 * 
 * All the code within this file has been written by me. See
 * linked_list.c for more details on any changes to the 
 * implementation that I made for the assignment.
 *
 * FILE:	linked_list.h
 * AUTHOR:	Syed Faraz Abrar (19126296)
 * UNIT:	COMP1000
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "helper.h"

/* This struct defines what each Node stored in the
 * linked list should contain. It stores a pointer to
 * the next node in the linked list, as well as a
 * string of size LINESIZE
 */
typedef struct Node
{
	struct Node *next;
	char str[LINESIZE];
} Node;

/* This struct defines the linked list itself.
 * It contains a pointer to the head of the linked list
 */
typedef struct
{
	Node *head;
} LinkedList;

/* This function inserts a Node at the end of the list */
void insertLast(Node **, char *);

/* This function recursively frees the whole list */
void freeList(Node **);

#endif
