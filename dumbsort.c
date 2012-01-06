#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i;

void swap(int *ptr1, int *ptr2) {
	if (*ptr1 == *ptr2)
		return;
	int tmp;
	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

void randomize_list(int list[], int len);
int is_sorted(int list[], int len);

void dumbsort(int list[], int len) {

srand(time(NULL));

	while (!is_sorted(list, len))
		randomize_list(list, len);

}

void randomize_list(int list[], int len) {

int n;

for (n = 0; n < len; n++) {
	swap(&list[n], &list[1+(int) (len*1.0*rand()/(RAND_MAX+1.0)) - 1]);
}


}

int is_sorted(int list[], int len) {

int last = 0;
int n;

for (n = 0; n < len; n++)
	if (list[n] < last)
		return 0;
	else
		last = list[n];

return 1;

}


int main() {

int n;
int *list;


scanf("%i", &i);

list = (int *) malloc (i*sizeof(int));

for (n = 0; n < i; n++)
	scanf("%i", &list[n]);

dumbsort(list, i);

for (n = 0; n < i; n++)
	printf("%i ", list[n]);

printf("\n");
return 0;

}

