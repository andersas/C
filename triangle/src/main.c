#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"
#include "output.h"
#include "threesides.h"
#include "twosides.h"
#include "oneside.h"

int main(int argc, char *argv[]) {

double a,b,c,A,B,C,area;
double results[12];
int ret;
int s,v;

#ifdef WINDOZE

short int choice;

start:
#endif

a=b=c=A=B=C=area=0.0;

ret=s=v=0;

printf("Calculating triangles with sides, angles and area.\n");
printf("Tell me 3 things about a triangle, and I give you the rest.\n");
printf("\n");
printf("Input sides (0 for unknown):\n");
printf("a: ");
if (scanf("%lf", &a) != 1) {
	neednumber:
	printf("Needs to be a number\n");
	#ifdef WINDOZE
	goto end;
	#else
	exit(1);
	#endif
}
if (a < 0) {
	rubbish:
	printf("What?\n");
	#ifdef WINDOZE
	goto end;
	#else
	exit(2);
	#endif
}

printf("b: ");
if (scanf("%lf", &b) != 1)
	goto neednumber;

if (b < 0)
	goto rubbish;

printf("c: ");
if (scanf("%lf", &c) != 1)
	goto neednumber;

if (c < 0)
	goto rubbish;


s = (a>0.0)+(b>0.0)+(c>0.0); // number of sides given

if (s == 0.0)
	goto insufficient_info;

/* Now get the angles */

if (s+v != 3) {
	printf("\nInput angles in degrees (0 for unknown):\n");

	printf("A: ");
	if (scanf("%lf", &A) != 1)
		goto neednumber;

	if (A < 0 || A > 180) 
		goto rubbish;
	
	if (A > 0)
		v++;

}

if (s+v != 3) {
	printf("B: ");
	if (scanf("%lf", &B) != 1)
		goto neednumber;

	if (B < 0)
		goto rubbish;

	if (B*(B>0)+A*(A>0) > 180) {
		toomuchangle:
		printf("Too much angle!\n");
		#ifdef WINDOZE
		goto end;
		#else
		exit(3);
		#endif
	} 
	if (B > 0)
		v++;
}

if (s+v != 3) {
	printf("C: ");
	if (scanf("%lf", &C) != 1) 
		goto neednumber;

	if (C < 0) {
		goto rubbish;
	}
	if (C*(C>0) + B*(B>0) + A*(A>0) > 180)
		goto toomuchangle;
	
	if (C > 0)
		v++;
}


/* First let's get the angles right: */

if (A) A = deg2rad(A);
if (B) B = deg2rad(B);
if (C) C = deg2rad(C);


if ((s == 2 && v == 0)  || ( s == 1 && v == 1 && ~(a && A) && ~(b && B) && ~(c && C) )) {

	printf("\nInput area (0 for unknown):\n");

	printf("Area: ");
	if (scanf("%lf",&area) != 1)
		goto neednumber;

	if (area < 0)
		goto rubbish;

	if (area == 0)
		goto insufficient_info;

	if (s == 1) {
		/* Just calculate a side and go on */

		if (A && b) {
			c = area/(0.5 * b * sin(A));
		} else if (A && c) {
			b = area/(0.5 * c * sin(A));
		}

		if (B && a) {
			c = area/(0.5 * a * sin(B));
		} else if (B && c) {
			a = area/(0.5 * c * sin(B));
		}

		if (C && a) {
			b = area/(0.5 * a * sin(C));
		} else if (C && b) {
			a = area/(0.5 * b * sin(C));
		}

		s++;

	}

	/* That was the easy part, now for what to do
	   if there's 2 sides and one angle: */

	if (s == 2) {

		if (!a) {
			A = area/(0.5*b*c);
			if (A > 1.0 || A < -1.0) 
				goto badangle;
			A = asin(A);

			if (twosides(a,b,c,A,B,C,results) == 3) 
				goto badangleafter;

	printf("\nPlease note that these values are rounded:\n");

			output(1,results);
			A = deg2rad(180) - A;
			twosides(a,b,c,A,B,C,results);
			output(2,results);

		}

		if (!b) {
			B = area/(0.5*a*c);
			if (B > 1.0 || B < -1.0)
				goto badangle;
			B = asin(B);

			if (twosides(a,b,c,A,B,C,results) == 3)
				goto badangleafter;

	printf("\nPlease note that these values are rounded:\n");

			output(1,results);
			B = deg2rad(180) - A;
			twosides(a,b,c,A,B,C,results);
			output(2,results);

		}

		if (!c) {
                        C = area/(0.5*a*b);
                        if (C > 1.0 || C < -1.0)
                                goto badangle;
                        C = asin(C);

                        if (twosides(a,b,c,A,B,C,results) == 3)
                                goto badangleafter;

	printf("\nPlease note that these values are rounded:\n");

                        output(1,results);
                        C = deg2rad(180) - C;
                        twosides(a,b,c,A,B,C,results);
                        output(2,results);

		}

	goto allwasgood;

	badangle:
	printf("Impossible triangle!\n");
	badangleafter:
	#ifdef WINDOZE
		goto end;
	#else
		exit(9);
	#endif


	}


} 
if (s+v != 3) 
	goto insufficient_info;

/* We've got all the info we need! */
/* Let's start the calculation. */


/* Three sides is easy */
if (s == 3) {

	if (threesides(a,b,c,results)) { /* returns 1 on failure */
		#ifdef WINDOZE
		goto end;
		#else
		exit(4);
		#endif
	}

	printf("\nPlease note that these values are rounded:\n");

	output(0, results);
}

/* Handle two sides with one angle. */
/* This has the possibility of having two solutions */


if (s == 2 && v == 1) {

	ret = twosides(a,b,c,A,B,C,results);

	if (ret == 3) {
		#ifdef WINDOZE
		goto end;
		#else
		exit(7);
		#endif
	}

	printf("\nPlease note that these values are rounded:\n");

	if (ret == 1) {
		output(0, results);
	}

	if (ret == 2) {
		output(1, results);
		output(2, results+6);
	}

}

/* Handle one side and two angles */

if (s == 1 && v == 2) {
	if (a) ret = oneside(SIDE_A, a, A, B, C, results);
	if (b) ret = oneside(SIDE_B, b, A, B, C, results);
	if (c) ret = oneside(SIDE_C, c, A, B, C, results);

	if (ret) {
		printf("Oops! Programming error!\n");
		#ifdef WINDOZE
			goto end;
		#else
			exit(6);
		#endif
	}

	printf("\nPlease note that these values are rounded:\n");

	output(0,results);
}


allwasgood:


#ifdef WINDOZE
goto end;
#else
return 0;
#endif


insufficient_info:
printf("Not enought information to calculate triangle from.\n");

#ifdef WINDOZE

end:

printf("\nExit program: press 1\n");
printf("Run program again: press 2\n");
printf("? ");
scanf("%i",&choice);

if (choice == 1)
	return 0;
if (choice == 2)
	goto start;
goto end;

#endif

return 8;

}
