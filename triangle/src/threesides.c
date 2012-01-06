#include <stdio.h>
#include <math.h>
#include "threesides.h"


int threesides(double a, double b, double c, double results[6]) {

if (a >= b+c || b >= a+c || c >= a+b) {
	printf("No solution\n");
	return 1;
}

results[0] = a;
results[1] = b;
results[2] = c;
results[3] = acos((a*a - b*b - c*c)/(-2.0*b*c));
results[4] = acos((b*b - a*a - c*c)/(-2.0*a*c));
results[5] = acos((c*c - a*a - b*b)/(-2.0*a*b));


return 0;

}


