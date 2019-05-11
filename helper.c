/* This file contains helper functions that is used all throughout the
 * TurtleGraphics program
 *
 * FILE:	helper.c
 * AUTHOR:	Syed Faraz Abrar (19126296)
 * UNIT:	COMP1000
 */

#include "helper.h"

/*	A function that is used to round the imported int variable to the
 *	nearest int
 *	This is very similar to the implementation of the round() function
 *	in C99, found here: http://www.jbox.dk/sanos/source/lib/math.c.html
 */
int round(double n)
{
	double rounded;
	/* 	Must check to see if n is a negative or positive real number
	 *	as the rounding will depend on this
	 */
	if (n > 0.0)
	{
		/* Force rounded to be the next integer up, then check the difference
		 * between rounded and n
		 */
		rounded = ceil(n);
		if (rounded - n >= 0.5)
			rounded -= 1.0;
	}
	else
	{
		/* Force rounded to be the next integer up after taking its absolute
		 * value, then compare the difference between rounded and n
		 */
		rounded = ceil(n * -1);
		if (rounded + n > 0.5)
			rounded -= 1.0;

		/* Multiply rounded by -1 because n is < 0.0 */
		rounded = rounded * -1;
	}

	return (int) rounded;
}



/* 	A function that is used to convert a string to all uppercase
 *	Taken from my own implementation of convertToUpper from
 *	practical 4
 */
void convertToUpper(char *str)
{
	/* 	Used the ASCII chart from www.asciitable.com to
	 *	figure out the correct integer values to use
	 */
	while(*str != '\0')
	{
		if (*str >= 97 &&
			*str <= 122)
			*str = *str - 32;

		str++;
	}
}



/*	This function converts the imported theta (in degrees) to
 *	radians as required by the math.h sin() and cos() functions
 *	RADIANS = DEGREES * PI / 180.0
 */
double degToRad(double theta)
{
	double radians = theta * M_PI / 180.0;

	return radians;
}


/*	This function is a helper function that displays errors depending
 *	on the errorCode that is passed into it
 */
void printError(int errorCode)
{
	switch(errorCode)
	{
		case 2:
			fprintf(stderr, "ERROR: Invalid command found in file. Exiting...\n");
			break;
		case 3:
			fprintf(stderr, "ERROR: Invalid arguments found in file. Exiting...\n");
			break;
	}
}
