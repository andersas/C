#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

signed char board[9][9];


int soduku(int x, int y);

void dumpboard();

int main() {

	int i,n,c;

/* Read input from stdin to the board[][] array: */

	for (i = 0; i < 9; i++) {

		for (n = 0; n < 9; n++) {

			c = getchar();

/* Compare character values, not integer!
   (refer to the ASCII table)

   FIXME: Do this with the ctype library instead */

			if (c >= '0' && c <= '9') {
				board[i][n] = (char) c - '0';
			} else {
				n--; /* Ignore anything but numbers */
			}

		}

	}
/* Solve the puzzle: */

	printf("Solutions: %i\n", soduku(0,0));

/* The interresting code is at the bottom of this file */

#ifdef WINDOZE /* With gcc, toggle this with -DWINDOZE command line option. */
	printf("\n");
	printf("Press enter to exit program.\n");
	getchar();
	getchar();
#endif
	return 0;

}

void dumpboard() { /* Dump the board to the screen */

int i, n;
printf("\n");
	for (i = 0; i < 9; i++) {
		for (n = 0; n < 9; n++) {
			printf("%i ",board[i][n]);
		}
		printf("\n");
	}

printf("---------\n");

}



int promesing(int x, int y) { /* This is out backtrackking system. */

			      /* It could be made a lot faster, but
				 since it solves a normal sudoku in a hundreth
				 of a second, I didn't really bother.. */

/* check row */
int i,n;
int checks[10];
for (i = 0; i < 10; checks[i++] = 0); /* reset */
for (i = 0; i < 9; checks[board[y][i++]]++); /* loop through row */
for (i = 1; i < 10; i++) {
if (checks[i] > 1)
	return 0;
}

/* check cols */
			/* The same.. */
for (i = 0; i < 10; checks[i++] = 0);
for (i = 0; i < 9; checks[board[i++][x]]++);
for (i = 1; i < 10; i++) {
if (checks[i] > 1)
	return 0;
}

/* check square */
for (i = 0; i < 10; checks[i++] = 0); /* reset */


if (x < 3) /* TODO: Do this with modulo arithmetic instead. */
	x = 0;
else if (x < 6)
	x = 3;
else if (x < 9)
	x = 6;

if (y < 3)
	y = 0;
else if (y < 6)
	y = 3;
else if (y < 9)
	y = 6;


for (i = y; i < y + 3; i++)
	for (n = x; n < x + 3; n++) 
		checks[board[i][n]]++;

for (i = 1; i < 10; i++) {
if (checks[i] > 1)
	return 0;
}

return 1;

}



int soduku(int x, int y) { /* Our deary function */

int i;
int sum = 0;

if (x >= 9) { /* Next row */
x = 0;
y++;
}

if (y >= 9) {
	dumpboard(); /* We have a solution */
	return 1;
}



	if (board[y][x] != 0) {	
		return soduku(x+1, y);
	}

/* INTERRESTING CODE FOLLOWS: */

	for (i = 1; i <= 9; i++) {
		board[y][x] = i;
		if (promesing(x,y))
		sum += soduku(x+1, y);
	}

	board[y][x] = 0; /* Clean up */

/* END OF INTERRESTING CODE */

	return sum;

}
