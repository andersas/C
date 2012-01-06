#include <stdio.h>
#include <math.h>
#include "functions.c"


int main(int argc, char *argv[]) {

float a,b,c,A,B,C; /* The triangle */

int intsides = 0;
int intangles = 0;
int solutions = 0;
int returnval,whatnow;

float tmp;

a=b=c=A=B=C=0;

START:

printf("Tell me 3 things about a triangle, and i will tell you the rest!\n");

printf("Sides (0 for unknown):\n");
printf("a: ");
scanf("%f",&a);
if (a < 0) {
	printf("There is no such thing as a negative lenght!\n");
	returnval = 1;
	goto END;
}
printf("b: ");
scanf("%f",&b);
if (b < 0) {
	printf("There is no such thing as a negative lenght!\n");
	returnval = 1;
	goto END;
}
printf("c: ");
scanf("%f",&c);
if (c < 0) {
	printf("There is no such thing as a negative lenght!\n");
	returnval = 1;
	goto END;
}

if (a) intsides++;
if (b) intsides++;
if (c) intsides++;

if (intsides == 0) {
	printf("You need to give me at least one side\n");
	returnval = 1;
	goto END;
}


if (intsides == 3) {

	/* We have all the sides! */

	returnval = threesides(a,b,c,solutions);
	goto END;

}

printf("Angles (0 for unknown):\n");
printf("A: ");
scanf("%f",&A);
if (A < 0 || A >= 180) {
	printf("Wrong angle.\n");
	returnval = 1;
	goto END;
}

if (A) intangles++;

if (intangles + intsides < 3) {
        printf("B: ");
        scanf("%f",&B);
        if (B < 0 || B >= 180) {
                printf("Wrong angle.\n");
		returnval = 1;
		goto END;
        }
        if (B) intangles++;
}

if (intangles + intsides < 3) {
        printf("C: ");
        scanf("%f",&C);
        if (C < 0 || C >= 180) {
                printf("Wrong angle.\n");
		returnval = 1;
		goto END;
        }
        if (C) intangles++;
}


/* Convert angles from degrees to radians: */
if (A) A = deg2rad(A);
if (B) B = deg2rad(B);
if (C) C = deg2rad(C);


if (intangles + intsides < 3) {

	if (intsides == 1 && intangles == 1 || intsides == 2) {
		
		/* Calculare one more side and continue program */

		if (area(&a,&b,&c,&A,&B,&C)) {
			returnval = 1;
			goto END;
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
		returnval = 1;
		goto END;
	}
} 


if (intangles == 3 && A+B+C != 180) {
	printf("You are giving too many angles, ");
	printf("and the sum of them is not 180.\n");
	printf("I have no idea which of them is wrong, ");
	printf("so i'm QUITTING.\n");
	returnval = 1;
	goto END;
}


/* Ready to roll: */

if (intsides == 2) { /* User has supplied us with 2 sides. Thank you. */

	returnval = twosides(a,b,c,A,B,C);
	goto END;

}


/* User has only supplied us with 1 side.. We're gonna have to live with that. */
if (intsides == 1) { 

	returnval = oneside(a,b,c,A,B,C);
	goto END;

}

printf("Something is wrong...\n");
returnval = 2;
goto END;


END:
printf("\n");
printf("Exit program: press 1\n");
printf("Run program again: press 2\n");
printf("? ");
scanf("%i",&whatnow);
if (whatnow != 2 && whatnow != 1) goto END;

if (whatnow == 1) {
	return returnval;
}

if (whatnow == 2) {
a=b=c=A=B=C=0; /* reset values */
intsides = 0;
intangles = 0;
solutions = 0;
returnval=whatnow=0;
tmp = 0;
	goto START;
}

}
