#define VERSION "v. 2.2"

float deg2rad (float value) {

	return (M_PI/180)*value;

}

float rad2deg (float value) {

	return value*(180/M_PI);

}


void solution(float a, float b, float c, float A, float B, float C, int solution
) {

float area = 0.5*a*b*sin(C);

A = rad2deg(A);
B = rad2deg(B);
C = rad2deg(C);

printf("  ---------\n");
if (solution != 0) {
printf("Solution nr. %i:\n",solution);
}
printf("Sides:\n");
printf("a: %f\n", a);
printf("b: %f\n", b);
printf("c: %f\n", c);

printf("\nAngles:\n");
printf("A: %f\n", A);
printf("B: %f\n", B);
printf("C: %f\n", C);

printf("Area: %f\n",area); 

}

#include "threesides.c"
#include "twosides.c"
#include "oneside.c"
#include "area.c"
