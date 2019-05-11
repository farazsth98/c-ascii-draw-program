/*	This file contains the function that is the main loop of the program,
 *	as well as any other function that relates to any "plotting" that
 *	occurs within the TurtleGraphics program
 *	
 *	FILE:	plotter.c
 *	AUTHOR:	Syed Faraz Abrar (19126296)
 *	UNIT:	COMP1000
 */

#include "plotter.h"

/*	This function keeps track of all the variables while the
 *	turtle program is running. It would be safe to call this the
 *	main loop of the program
 *	Note that all the lines stored within the linked list will already
 *	be valid as they have been checked before being put into the linked list
 */
void draw(Node **head)
{
	Node *current = *head;
	char str[LINESIZE];
	char *token;
	FILE *log = fopen("graphics.log", "a");

	/* Variables to hold the command + its argument */
	char command[8]; /* "PATTERN" is the longest possible command */

	/* Temporary variables used when printing to the log file:
	 * These are required because the actual x and y values must
	 * be rounded off after every MOVE and DRAW command in order
	 * to ensure the cursor is at an integer location on the screen
	 * because the terminal cannot place the cursor in between two
	 * integer points
	 */
	double tempX = 0.0, tempY = 0.0;

	/* Default variable values, as per the assignment brief */
	double x = 0.0, y = 0.0;
	double theta = 0.0;
	int fg = 7, bg = 0;
	char pattern = '+';

	/* If the compile flag "SIMPLE" is used, then fg should be 0 and bg should be 7 */
	#ifdef SIMPLE
	fg = 0; bg = 7;
	#endif

	/* Ensure the log file actually opens */
	if (log == NULL)
		perror("Error opening log file");
	else
	{
		setFgColour(fg);
		setBgColour(bg);

		clearScreen();

		fprintf(log, "---\n");
		while (current != NULL)
		{
			/*	Use strtok to tokenize each line from the linked list
			 *	and store them in their respective variables
			 */
			strcpy(str, current->str);
			token = strtok(str, " ");

			/* Store the command and go to the next token immediately */
			strcpy(command, token);
			convertToUpper(command);
			token = strtok(NULL, " ");
	
			if (strcmp(command, "ROTATE") == 0)
				theta += atof(token);
			else if (strcmp(command, "MOVE") == 0)
			{
				fprintf(log, "MOVE (%8.3f, %8.3f)-(", tempX, tempY);

				#ifdef DEBUG
				fprintf(stderr, "MOVE (%8.3f, %8.3f)-(", tempX, tempY);
				#endif
				
				/* Simply change the x and y values accordingly to keep
				 * track of where the cursor is currently
				 */
				move(&x, &y, atof(token), theta);
				fprintf(log, "%8.3f, %8.3f)\n", x, y);
				
				#ifdef DEBUG
				fprintf(stderr, "%8.3f, %8.3f)\n", x, y);
				#endif

				tempX = x; tempY = y;

				/* Round off x and y values so the cursor is placed at integer
				 * valued coordinates
				 */

				x = round(x);
				y = round(y);
			}
			else if (strcmp(command, "DRAW") == 0)
			{
				fprintf(log, "DRAW (%8.3f, %8.3f)-(", tempX, tempY);

				#ifdef DEBUG
				fprintf(stderr, "DRAW (%8.3f, %8.3f)-(", tempX, tempY);
				#endif

				tempX = x; tempY = y;
				
				/* 	atof(token)-1 in order to reduce the distance by 1
				 *	to prevent the double printing error from occuring
				 */
				move(&x, &y, atof(token)-1, theta);

				/* 	Draws a line from (tempX, tempY) to (x, y) with the character
				 * 	stored in the pattern variable
				 */
				line(round(tempX), round(tempY), round(x), round(y), 
					&plot, &pattern);
				
				/* Move cursor over by 1 to prevent the double printing error */
				move(&x, &y, 1, theta);
				fprintf(log, "%8.3f, %8.3f)\n", x, y);

				#ifdef DEBUG
				fprintf(stderr, "%8.3f, %8.3f)\n", x, y);
				#endif

				tempX = x; tempY = y;

				/* Round off x and y values so the cursor is placed at integer
				 * valued coordinates
				 */
				x = round(x);
				y = round(y);
			}
			else if (strcmp(command, "FG") == 0)
			{
				/* Ensure the compile flag "SIMPLE" is not set */
				#ifndef SIMPLE
				fg = atoi(token);
				setFgColour(fg);
				#endif
			}
			else if (strcmp(command, "BG") == 0)
			{
				/* Ensure the compile flag "SIMPLE" is not set */
				#ifndef SIMPLE
				bg = atoi(token);
				setBgColour(bg);
				#endif
			}
			else if (strcmp(command, "PATTERN") == 0)
			{
				pattern = *token; /* Token only has one character in it */
			}

			current = current->next;
		}

		penDown();

		fclose(log);
	}
}


/*	This function modifies the imported x and y coordinate values
 *	in order to reflect movement by d units at an angle of theta
 */
void move(double *x, double *y, double d, double theta)
{
	double deltaX = 0.0, deltaY = 0.0;
	double radians = degToRad(theta);
	
	/* 	Calculation of deltaX and deltaY done using the formulas provided
	 *	in the assignment brief.
	 *	NOTE: deltaY is multiplied by -1.0 because of the way the y axis
	 *	is inverted for the program (i.e y++ is down and y-- is up)
	 */
	deltaX = d * cos(radians);
	deltaY = d * sin(radians) * -1.0;

	*x += deltaX;
	*y += deltaY;

	/* Check to ensure the x and y values aren't less than 0 
	 * If they are, set them to 0
	 */
	if (*x < 0) *x = 0.0;
	if (*y < 0) *y = 0.0;
}


/* This function is passed to the line() function defined in
 * effects.h
 * Its main purpose is to handle drawing the plotData passed to
 * it onto the screen
 */
void plot(void *plotData)
{
	/* The function will never be passed anything other than a char
	 * so it is safe to typecast the plotData to a char immediately
	 */
	char data = *((char *) plotData);
	printf("%c", data);
}
