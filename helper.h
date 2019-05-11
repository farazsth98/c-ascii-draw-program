/* FILE:	helper.h
 * AUTHOR:	Syed Faraz Abrar (19126296)
 * UNIT:	COMP1000
 */

#ifndef HELPER_H
#define HELPER_H

#include <math.h>
#include <stdio.h>

/* The assumed maximum length of a line from the input file */
#define LINESIZE 30

/* PI approximated to 20 decimal points */
#define M_PI 3.14159265358979323846

/* A function that rounds the imported double to the nearest integer value */
int round(double);

/* A function that converts the imported char * to all uppercase characters 
 * It is based on my own implementation of the function from practical 4
 */
void convertToUpper(char *);

/* A function that converts the imported degrees (double) into radians (double) */
double degToRad(double);

/* A helper function that prints out an error depending on the imported integer */
void printError(int);

#endif
