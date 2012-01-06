#include <stdio.h>
#include <math.h>
#include "functions.h"

/* sides and angles in the results[] array */

#define SA 0
#define SB 1
#define SC 2
#define AA 3
#define AB 4
#define AC 5


/* Return values: 1 for 1 solution, 2 for two solutions, 3 for errors */


int twosides (double a, double b, double c, double A, double B, \
	      double C, double results[12]) {

int solutions = 1;
int rotations = 0;
double tmp;

/*
 * First rotate the triangle, to make the possible
 * solutions fewer.
 */


while (A == 0.0) {

tmp = a;
a = b;
b = c;
c = tmp;

tmp = A;
A = B;
B = C;
C = tmp;

rotations++;

}

results[SA] = a;
results[SB] = b;
results[SC] = c;
results[AA] = A;
results[AB] = B;
results[AC] = C;
results[SA+6] = a;
results[SB+6] = b;
results[SC+6] = c;
results[AA+6] = A;
results[AB+6] = B;
results[AC+6] = C;




if (a && b) {
	B = b*sin(A)/a;

	if (B > 1.0 || B < -1.0) {
		printf("Impossible triangle!\n");
		return 3;
	}

	results[AB] = asin(B);

	if (deg2rad(180)-results[AB]+A < deg2rad(180)) {

		solutions = 2;
		results[AB+6] = deg2rad(180) - results[AB];
		results[AC+6] = deg2rad(180) - results[AB+6] - A;
		
		results[SC+6] = sqrt(a*a+b*b-2*a*b*cos(results[AC+6]));

	}

	results[AC] = deg2rad(180) - results[AB] - A;
	results[SC] = sqrt(a*a+b*b-2*a*b*cos(results[AC]));
}

if (a && c) {

	C = c*sin(A)/a;

	if (C > 1.0 || C < -1.0) {
		printf("Impossible triangle!\n");
		return 3;
	}
	
	results[AC] = asin(C);

	if (deg2rad(180)-results[AC]+A < deg2rad(180)) {

		solutions = 2;

		results[AC+6] = deg2rad(180) - results[AC];
		results[AB+6] = deg2rad(180) - results[AC+6] - A;

		results[SB+6] = sqrt(a*a+c*c-2*a*c*cos(results[AB+6]));

	}

	results[AB] = deg2rad(180) - results[AC] - A;
	results[SB] = sqrt(a*a+c*c-2*a*c*cos(results[AB+6]));
}

if (b && c) {

	results[SA] = sqrt(b*b+c*c-2*b*c*cos(A));
	results[AB] = acos((b*b-results[SA]*results[SA]-c*c)/(-2*results[SA]*c));
	results[AC] = deg2rad(180) - results[AB] - A;

}




/*
 * Rotate the triangle back
 */


while (rotations) {

tmp = results[SC];
results[SC] = results[SB];
results[SB] = results[SA];
results[SA] = tmp;

tmp = results[AC];
results[AC] = results[AB];
results[AB] = results[AA];
results[AA] = tmp;

if (solutions == 2) {

tmp = results[SC+6];
results[SC+6] = results[SB+6];
results[SB+6] = results[SA+6];
results[SA+6] = tmp;

tmp = results[AC+6];
results[AC+6] = results[AB+6];
results[AB+6] = results[AA+6];
results[AA+6] = tmp;

}

rotations--;

}

return solutions;

}

