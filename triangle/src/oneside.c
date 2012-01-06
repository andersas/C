#include <math.h>
#include "oneside.h"
#include "functions.h"

int oneside (char which, double side, double A, double B, double C, \
	     double results[6]) {

if (!A) A = deg2rad(180) - B - C;
if (!B) B = deg2rad(180) - A - C;
if (!C) C = deg2rad(180) - A - B;

results[3] = A;
results[4] = B;
results[5] = C;

if (which == SIDE_A) {
	results[0] = side;
	results[1] = (side*sin(B))/sin(A);
	results[2] = (side*sin(C))/sin(A);
}
if (which == SIDE_B) {
	results[0] = (side*sin(A))/sin(B);
	results[1] = side;
	results[2] = (side*sin(C))/sin(B);
}
if (which == SIDE_C) {
	results[0] = (side*sin(A))/sin(C);
	results[1] = (side*sin(B))/sin(C);
	results[2] = side;
}

if (which != SIDE_A && which != SIDE_B && which != SIDE_C)
	return 1;


return 0;

}

