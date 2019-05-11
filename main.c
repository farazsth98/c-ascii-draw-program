/* This file contains the main function for the program */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "helper.h"
#include "io.h"
#include "plotter.h"

int main(int argc, char **argv)
{
	int errorCode = 0; /* Used to check if an error occurred */
	LinkedList *list = NULL;

	if (argc != 2)
	{
		printf("Usage: %s <inputfilename>\n", argv[0]);
	}
	else
	{
		/* 	The linked list is defined and initialized here
		 *	because it is passed between two functions
		 */
		list = (LinkedList *) malloc (sizeof(LinkedList));
		list->head = NULL;

		/* 	parseLine goes through each line in the filename passed into
		 *	it through argv[1], error checking and then putting the line
		 *	into the linked list
		 */
		errorCode = parseLine(argv[1], &list->head);
		if (errorCode)
			printError(errorCode);
		else
		{
			draw(&list->head); /* Main loop of the program */
		}

		freeList(&list->head);
		free(list);
	}

	return 0;
}
