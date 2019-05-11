/*	FILE:	plotter.h
 *	AUTHOR:	Syed Faraz Abrar (19126296)
 *	UNIT:	COMP1000
 */

#ifndef PLOTTER_H
#define PLOTTER_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "linked_list.h"
#include "effects.h"

/* 	This function is the main loop of the program
 * 	It loops through each line in the linked list
 * 	that is passed into it, executes each command
 * 	with its corresponding argument
 * 	NOTE: The lines within the linked list are all
 * 	valid as they have been error checked prior to
 * 	this function being called
 */
void draw(Node **head);

/*	This function takes in the memory addresses of
 *	the x and y variables, as well as the distance
 *	to move and the angle to move at
 *	It modifies the x and y variables to reflect the
 *	new coordinates where the cursor sits
 */
void move(double *, double *, double, double);

/*	This is the helper function that is called by the
 *	predefined line() command in the effects.c file.
 *	Its purpose is to print out the data that is passed
 *	to it
 */
void plot(void *);

#endif
