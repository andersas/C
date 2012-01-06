#include <stdio.h>
#include <math.h>
#include "functions.h"
#include "output.h"


void output(int result_nr, double results[6]) {

printf("\n");
if (result_nr != 0) {
printf("Solution nr. %i:\n",result_nr);
}

printf("a: %.9f\n", results[0]);
printf("b: %.9f\n", results[1]);
printf("c: %.9f\n", results[2]);
printf("A: %.9f\n", rad2deg(results[3]));
printf("B: %.9f\n", rad2deg(results[4]));
printf("C: %.9f\n", rad2deg(results[5]));
printf("Area: %.9f\n", 0.5 * results[0] * results[1] * sin(results[5]));


return;

}


