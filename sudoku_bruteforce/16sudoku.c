#include <stdio.h>
#include <stdlib.h>

/* This is the basic principle of solving a sudoku (my way at least):
 * - See if fields only have one possible value
 * - See if a field is the only field in subsquare/row/column
 *   that can take a particular value
 * - Realizing that this row/col in a subsquare must
 *   contain some value and consequently
 *   remove that value from possibilities
 *   in the entire row/column.
 */



#define BOARDSIZE 16 // TODO: Read this from argv (hint: must be square number)
int nsquares = 4;  // NOTE: This has to be the integer square root of the boardsize
struct queuepoint {
	int y;
	int x;
	int remove_possibility;
	struct queuepoint *next;
};

typedef char postype;
typedef struct {
	int definite_value;
	postype *possibilities;
} cell;

cell board[BOARDSIZE][BOARDSIZE];

// Here follows a whole lot of small creepy subfunctions:
int possible(int val, int y, int x);
int square_remove(int val, int y, int x);
int horiz_remove(int val, int y, int x);
int vert_remove(int val, int y, int x);
int iamtheonly(int y, int x); /* TODO */
void setcell(int val, int y, int x);
void clean_queue(); /* TODO */
void load_board(); /* TODO */
int do_something();
void dump_board();
int lenghtofnumber(int i);
void push(struct queuepoint insertion);
struct queuepoint pop();

struct queuepoint *first, *last;

int main(int argc, char *argv[]) {

int i;
first = NULL;
last = NULL;

load_board();

i = do_something();
if (i) {
	printf("Could not solve the last %i fields...\n", i);
	printf("Here is what I could solve:\n\n");
} else {
	printf("Here is the solution:\n\n");
}

dump_board();

return 0;
}

int possible(int val, int y, int x) {
	return (int) board[y][x].possibilities[val-1];
}

int square_remove(int val, int y, int x) {
/* The sudoku board is split into subsquares of isqrt(n) lenght.
   This routine marks every field of the board inside the current
   subsquare, so that the current value will be removed from the 
   list of possible values of each field. It does not do this
   on fields where this possibility is already gone, since
   we'd run into an infinite loop if we did... */

struct queuepoint rm;
int i;
int xsquare, ysquare;

xsquare = x / nsquares; /* Find out wich square we're in */
ysquare = y / nsquares;

rm.remove_possibility = val; /* Mark this value as impossible */

i = 0;
/* Note: nsquares contains the isqrt of the board size      v v v v v*/
for (rm.y = ysquare * nsquares; rm.y < ysquare * nsquares + nsquares; rm.y++) {
for (rm.x = xsquare * nsquares; rm.x < xsquare * nsquares + nsquares; rm.x++) {
	if (possible(val, y, x)) {
		push(rm); /* Mark impossible */
		i = 1;
	}
}
}

return i;

}

/* The same story for the next two functions. They just
   mark the columns and rows instead of the current subsquare */

int horiz_remove(int val, int y, int x) {

int i;
struct queuepoint rm;
rm.x = 0;
rm.y = y;
rm.remove_possibility = val;

i = 0;

while (rm.x < BOARDSIZE && rm.x != x) {
	if (possible(val, y, x)) {
		push(rm);
		i = 1; /* if i == 0, but checking is redundant. */
	}

	rm.x++;
}

return i;

}

int vert_remove(int val, int y, int x) {

int i;
struct queuepoint rm;
rm.x = x;
rm.y = 0;
rm.remove_possibility = val;

i = 0;

while (rm.y < BOARDSIZE && rm.y != y) {
	if (possible(val, y, x)) {
		push(rm);
		i = 1;
	}

	rm.y++;
}

return i;

}

void load_board() {

}

int do_something() {

int i, n, x, y, tmp;

i = BOARDSIZE*BOARDSIZE; /* i counts number of empty (undetermined) fields */
/* n is the number of unsolved fields in the last run */
do {
n = i;
i = 0;
clean_queue(); /* clean queue goes through the list of fields to be
		  processed. This loop adds to the queue and so
		  does the input function whenever it encounters
		  a defined input value (= filled out field of the sudoku). */
for (y = 0; y < BOARDSIZE; y++) {
	for (x = 0; x < BOARDSIZE; x++) {

		tmp = iamtheonly(y, x);
		if (tmp) {
			setcell(tmp, y, x);
		} else
			if (tmp == 0 && board[y][x].definite_value == 0)
				i++;
	}
}

} while (i != n);

return i;

}

int iamtheonly(int y, int x) {

	/* In this function, we build an array of
	   lists of possibilities in the fields that
	   concern us. That is all fields except the
	   x,y field we are on that are in our subsquare
	   and are horizontal and vertically on our line.

	   Then, for each of our own possibilities, we search
	   through the found lists of possibilities, and if
	   all other possibilities are 0 (false) we are
	   the only field that can have that value.
	   Thus we return that value. (we also check
	   to see if there are more values for which we are
	   the only possible field. In this case, the given sudoku
	   board is bogus) */

postype **possibilities;
int nmemb;
int retval;
int p, q;

/* nmemb: number of cells vertical, horizontal and in the current square,
 * excluding current cell */
nmemb = 2*(BOARDSIZE-nsquares) + nsquares*nsquares-1;
possibilities = (postype **) malloc(sizeof(postype *)*nmemb);

/* some algorithm to fill possibilities goes here */

retval = 0;
for (p = 1; p <= BOARDSIZE; p++) {
	if (board[y][x].possibilities[p] != 1)
		continue;

	for (q = 0; q < nmemb; q++) {
		if ("???")

	}
}

free(possibilities);

}


void dump_board() {

int y, x, width;

width = lenghtofnumber(BOARDSIZE - 1);

for (y = 0; y < BOARDSIZE; y++) {

	for (x = 0; x < BOARDSIZE - 1; x++) {
		printf("%*i ", width, board[y][x].definite_value);
		if (x % nsquares == nsquares - 1)
			printf(" ");
	}
		printf("%*i", width, board[y][x].definite_value);

	printf("\n");
	if (y % nsquares == nsquares - 1 && y != BOARDSIZE - 1)
		printf("\n");

}

return;
}

void setcell(int val, int y, int x) {
int n;
	for (n = 0; n < BOARDSIZE; n++) {
		board[y][x].possibilities[n] = 0;
	}
	board[y][x].possibilities[val - 1] = 1;
	board[y][x].definite_value = val;

	square_remove(val, y, x);
	horiz_remove(val, y, x);
	vert_remove(val, y, x);
return;
}

/* Functions for pushing and popping marked fields on and off a queue */
void push(struct queuepoint insertion) {

	
if (last != NULL) {
	last -> next = (struct queuepoint *) malloc(sizeof(struct queuepoint));
	last = last -> next;
} else
	last = first = (struct queuepoint *) malloc(sizeof(struct queuepoint));
	
last -> y = insertion.y;
last -> x = insertion.x;
last -> remove_possibility = insertion.remove_possibility;
last -> next = NULL;


return;
}
	
struct queuepoint pop() {

/* pop() does not check for empty queue!!! (it doesn't need to) */

struct queuepoint a;
a.x = first -> x;
a.y = first -> y;
a.remove_possibility = first -> remove_possibility;
a.next = first -> next;
free(first);
first = a.next;

if (first == NULL)
	last = NULL;

return a;
}

int lenghtofnumber(int i) {

int len = 1;

if (i < 0) len++;

while (i /= 10) len++;

return len;

}
