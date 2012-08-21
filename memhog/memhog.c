#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

double amount;
char *buf;
size_t s_amount;
size_t i;

if (argc != 2) {
	fprintf(stderr,"Specify amount of memory (in MB) to hog.\n");
	exit(1);
}

amount = atof(argv[1]);
if (amount < 0) {
	fprintf(stderr,"Specify a positive amount of memory (in MB) to hog.\n");
	exit(1);
}

printf("Taking up %.2f MB of memory...\n", amount);

s_amount = amount*1024*1024;

buf = (char *) malloc(s_amount);

/* Touch the memory, or the OS won't actually allocate the pages */
for (i = 0; i < s_amount; i++) {

buf[i] = i%4679;

}

printf("Press enter to exit.");

getchar();

return 0;
}
