/* 	FILE:	io.h
 *  AUTHOR:	Syed Faraz Abrar (19126296)
 *  UNIT:	COMP1000
 */

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "linked_list.h"

/* 	This function error checks each line in the file
 *	name that is passed in as its first argument, and then
 *	stores the lines in a linked list.
 *	Returns an integer, where 0 indicates no error
 */
int parseLine(char *, Node **);

/* 	Helper function for parseLine, ensures that the file doesn't
 *	contain any unknown commands.
 *	Allowed commands: rotate, move, draw, fg, bg, pattern
 */
char parseCommand(char *);

/*	Helper function for parseLine, ensures that the file doesn't
 *	contain any incorrect arguments, and that the file actually
 *	contains the correct number of arguments
 */
int parseArgs(char *, char);

#endif
