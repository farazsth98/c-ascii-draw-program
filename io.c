/*	This file contains functions that relate to File I/O
 *	The functions go through each line in the input file,
 *	error check them to ensure they are completely valid and
 *	then store them in a linked list
 *
 *	FILE:	io.c
 *	AUTHOR:	Syed Faraz Abrar
 *	UNIT:	COMP1000
 */

#include "io.h"

/*	This function parses the lines in the input file,
 *	only stopping when everything has been parsed or when
 *	an error has occurred. The type of error is determined
 *	by the value that the errorCode is set to
 *	returns the errorCode
 */
int parseLine(char *filename, Node **head)
{
	int args, errorCode = 0;
	char line[LINESIZE];
	char command;
	FILE *input = fopen(filename, "r");
	
	if (input == NULL)
	{
		perror("Error opening input file");
		errorCode = 1;
	}
	else
	{
		while (fgets(line, LINESIZE, input) != NULL && !errorCode)
		{
			command = parseCommand(line);
			if (command == 'e') errorCode = 2;

			args = parseArgs(line, command);
			if (args != 2) errorCode = 3;

			insertLast(head, line);
		}

		fclose(input);
	}

	return errorCode;
}



/*	This function tries to read one string from the imported str string,
 *	converts it to uppercase and compares it to all of the commands that
 *	have been specified by the assignment brief. It then returns a character
 *	that corresponds to each command's first letter, or 'e' for an invalid 
 *	command
 */
char parseCommand(char *str)
{
	 /* 'pattern' is the longest command possible of size 7
	  * add one to that size for the NULL terminator.
	  */
	char command[8];
	char temp = '\n'; /* Used to read the blank space after the command */
	int cLength;
	
	/* 	This variable is a one character symbol for each command possible
	 *	'r' = rotate, 'm' = move, 'd' = draw, 'f' = fg, 'b' = bg, 'p' = pattern
	 *	If a line does not start with one of the above commands, the character
	 *	'e' is returned to signify that the command is invalid
	 */
	char symbol;

	/* Read the first 7 characters into the command variable, and the next 
	 * character into the temp variable. Ensure that temp is a blank space as
	 * otherwise, the command is invalid. Also ensure that both variables are
	 * read into.
	 */
	if (sscanf(str, "%7s%c", command, &temp) != 2 || temp != ' ')
	{
		symbol = 'e';
	}
	else
	{
		convertToUpper(command);

		/* First ensure that the command length is between 2 and 7 inclusive */
		cLength = strlen(command);

		if (cLength > 7|| cLength < 2)
			symbol = 'e';
		else
		{
			/* Then use strcmp() to check the command with the actual commands
			 * as mentioned in the assignment brief
			 */
			switch(cLength)
			{
				case 2:
				{
					if (strcmp(command, "FG") == 0) symbol = 'f';
					else if (strcmp(command, "BG") == 0) symbol = 'b';
					else symbol = 'e';
					break;
				}
				case 4:
				{
					if (strcmp(command, "MOVE") == 0) symbol = 'm';
					else if (strcmp(command, "DRAW") == 0) symbol = 'd';
					else symbol = 'e';
					break;
				}
				case 6:
				{
					if (strcmp(command, "ROTATE") == 0) symbol = 'r';
					else symbol = 'e';
					break;
				}
				case 7:
				{
					if (strcmp(command, "PATTERN") == 0) symbol = 'p';
					else symbol = 'e';
					break;
				}
				default:
					symbol = 'e';
			}
		}
	}
	return symbol;
}


/*	This function checks to make sure that the imported character string
 *	does not contain more than two tokens. It returns the number of tokens read,
 *	which is then checked in the parseLine() function to make sure the line is
 * 	in the correct format
 * 	It then checks to make sure that the argument is of the correct format for
 * 	the command type specified by the 'symbol' variable that is imported in
 * 	Returns 2 for a success, 0 for a fail.
 */
int parseArgs(char *str, char symbol)
{
	/* Two temp variables used to tokenize the str twice */
	char temp[LINESIZE], temp2[LINESIZE];
	char *token;
	int n = 0; /* Stores the number of tokens */
	int integerInput = -1;
	double realInput;
	char charInput, newLine;

	strcpy(temp, str);
	strcpy(temp2, str);

	/* Tokenize the first temp variable and ensure that there are only
	 * two tokens in it
	 */
	token = strtok(temp, " ");

	while (token != NULL)
	{
		n++;
		token = strtok(NULL, " ");
	}
	
	if (n == 2)
	{
		/* Now check to ensure the argument is of the correct type */
		token = strtok(temp2, " ");
		token = strtok(NULL, " ");

		/* Use the passed in symbol to ensure the correct data type + a new line
		 * character is entered. Otherwise, set n=0 to show that an error occurred
		 * This solution is adapted from a solution to a similar problem found in this
		 * stackoverflow post: https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
		 */
		switch(symbol)
		{
			case 'r': case 'm': case'd':
			{
				if (sscanf(token, "%lf%c", &realInput, &newLine) != 2 || newLine != '\n')
					n = 0; /* Set n to 0 to show that an error occurred */
				break;
			}
			case 'f':
			{
				if (sscanf(token, "%d%c", &integerInput, &newLine) != 2 || newLine != '\n')
				{
					n = 0; /* Set n to 0 to show that an error occurred */
				}

				if (integerInput < 0 || integerInput > 15)
					n = 0; /* FG is a value between 0 and 15 inclusive */
				break;
			}
			case 'b':
			{
				if (sscanf(token, "%d%c", &integerInput, &newLine) != 2 || newLine != '\n')
				{
					n = 0; /* Set n to 0 to show that an error occurred */
				}

				if (integerInput < 0 || integerInput > 7)
					n = 0; /* BG is a value between 0 and 7 inclusive */
				break;
			}
			case 'p':
			{
				if (sscanf(token, "%c%c", &charInput, &newLine) != 2 || newLine != '\n' 
					|| charInput == '\n' || charInput == ' ')
					n = 0; /* Set n to 0 to show that an error occurred */
				break;
			}
		}
	}

	return n;
}
