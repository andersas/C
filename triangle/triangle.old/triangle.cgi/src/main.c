#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "functions.c"


int main(int argc, char *argv[]) {


float a,b,c,A,B,C; /* The triangle */

int intsides = 0;
int intangles = 0;
int solutions = 0;

float tmp;

if (argc != 8) {
	printf("Inputerror!\n");
	return 1;
}

a=atof(argv[1]);
b=atof(argv[2]);
c=atof(argv[3]);

if (a < 0 || b < 0 || c < 0) {
	printf("There is no such thing as a negative lenght!\n");
	return 1;
}

if (a) intsides++;
if (b) intsides++;
if (c) intsides++;

if (intsides == 0) {
	printf("You need to give me at least one side\n");
	return 1;
}


if (intsides == 3) {

	/* We have all the sides! */

	return threesides(a,b,c,solutions);

}

A=atof(argv[4]);
B=atof(argv[5]);
C=atof(argv[6]);

if (A < 0 || A >= 180 || B < 0 || B >= 180 || C < 0 || C >= 180) {
	printf("Wrong angle.\n");
	return 1;
}

if (A) intangles++;
if (B) intangles++;
if (C) intangles++;

/* Convert angles from degrees to radians: */
if (A) A = deg2rad(A);
if (B) B = deg2rad(B);
if (C) C = deg2rad(C);


if (intangles + intsides < 3) {

	if (intsides == 1 && intangles == 1 || intsides == 2) {
		
		/* Calculare one more side and continue program */

		if (area(&a,&b,&c,&A,&B,&C,atof(argv[7]))) {
			return 1;
		}
		intangles = 0;
		intsides = 0;
		if (a) intsides++;
		if (b) intsides++;
		if (c) intsides++;
		if (A) intangles++;
		if (B) intangles++;
		if (C) intangles++;
		
	} else {
		printf("Not enough information.\n");
		return 1;
	}
} 



if (intangles == 3 && A+B+C != deg2rad(180)) {
	printf("You are giving too many angles, ");
	printf("and the sum of them is not 180.\n");
	printf("I have no idea which of them is wrong, ");
	printf("so i'm QUITTING.\n");
	return 1;
}


/* Ready to roll: */


if (intsides == 2) { /* User has supplied us with 2 sides. Thank you. */

	return twosides(a,b,c,A,B,C);

}


/* User has only supplied us with 1 side.. We're gonna have to live with that. */
if (intsides == 1) { 

	return oneside(a,b,c,A,B,C);

}

printf("Something is wrong...\n");
return 2;

}
