#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a,b) = (a < b) ? a : b
#define max(a,b) = (a > b) ? a : b

long long int prime(unsigned long long int num) {

	unsigned long long int base,stop;

	if (num % 2 == 0 || num % 3 == 0)
		return 0;

	stop = (long long int) sqrt(num) + 1;
	for (base = 6; base < stop; base += 6) {
		if (num % (base - 1) == 0 || num % (base+1) == 0)
			return 0;
	}

	return 1;

}

int main(int argc, char **argv) {


	unsigned long long int a,b;

	if (argc != 3) {
		printf("Usage: prime <start> <stop>\n");
		printf("Finds prime numbers between <start> and <stop>\n");
		return 1;
	}

	a = atoll(argv[1]);
	b = atoll(argv[2]);

	if (a < 5) {
		if (a <= 2) printf("2\n");
		if (a <= 3) printf("3\n");
	}

	a = (a > 6) ? a : 6;

	for (; a < b; a += 6) {

		if (prime(a-1))
			printf("%lli\n",a-1);
		if (prime(a+1))
			printf("%lli\n",a+1);
	}


return 0;

}
