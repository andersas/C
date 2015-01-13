#include <stdio.h>


#define max(a,b) (a > b) ? a : b
#define min(a,b) (a < b) ? a : b

int prime(unsigned int num) {

	unsigned int base;

	if (num % 2 == 0 || num % 3 == 0)
		return 0;

	for (base = 6; base*base < num; base += 6) {
		if (num % (base - 1) == 0 || num % (base+1) == 0)
			return 0;
	}

	return 1;

}

int main(int argc, char **argv) {


	unsigned int a,b;

	if (argc != 3) {
		printf("Usage: prime <start> <stop>\n");
		printf("Finds prime numbers between <start> and <stop>\n");
		return 1;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	if (a < 6) {
		if (a <= 2) printf("2\n");
		if (a <= 3) printf("3\n");
		if (a <= 5) printf("5\n");
	}

	a = (a > 6) ? a : 7;

	if (a%6 != 0) {
		a = a - a%6;
		if (a < b && prime(a+1))
			printf("%i\n", a+1);
		a +=6;
	}

	for (; a <= b +1; a += 6) {

		if (a-1 <= b && prime(a-1))
			printf("%i\n",a-1);
		if (a + 1 <= b && prime(a+1))
			printf("%i\n",a+1);
	}


return 0;

}
