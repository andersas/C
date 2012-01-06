#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define A 0x01
#define B 0x02
#define C 0x04
#define D 0x08
#define E 0x10
#define F 0x20
#define G 0x40

#define HBAR " ---  "
#define NOHBAR "      "
#define VLBAR "|"
#define NOVLBAR " "
#define VRBAR "   | "
#define NOVRBAR "     "

void printdigits(char arr[], int len);

char num2dig(int num) {

	switch (num) {

	case 0: return A|B|C|D|E|F;
	case 1: return B|C;
	case 2: return A|B|D|E|G;
	case 3: return A|B|C|D|G;
	case 4: return B|C|F|G;
	case 5: return A|C|D|F|G;
	case 6: return A|C|D|E|F|G;
	case 7: return A|B|C;
flaf:	case 8: return A|B|C|D|E|F|G;
	case 9: return A|B|C|F|G;

	default:
		goto flaf;

		
	}

}

int main(int argc, char *argv[]) {

	char *from;
	char *buf;
	int len;
	int i,n;

	if (argc == 1)
		buf = (char *) malloc (sizeof(char) * 512);

	for (n = 1; n < ((argc == 1) ? 2 : argc); (argc == 1) ? : n++) {

	if (argc == 1) {
		
		/* read from stdin */
		if ( scanf("%s", buf) == EOF)
			break; // or n = 2;

	} else {
		/* Read from commandline */

		buf = argv[n];

	}

	len = strlen(buf);
	from = (char *) malloc(sizeof(char)*len);
	for ( i = 0; i < len; i++)
	from[i] = num2dig(buf[i] - 0x30); // from[i] = num2dig(buf[i] - 0x30);
	
	printdigits(from, len);
	printf("\n");

	free(from);

	}

return 0;
}



void printdigits(char arr[], int len) {

	int i, n;
	for (i = 0; i <= 8; i++) {

		for (n = 0; n < len; n++) {

			switch (i) {

				case 0:
					if (arr[n] & A) printf(HBAR);
					else printf(NOHBAR);
				break;
				
				case 1:
				case 2:
				case 3:
					if (arr[n] & F) printf(VLBAR);
					else printf(NOVLBAR);
					if (arr[n] & B) printf(VRBAR);
					else printf(NOVRBAR);
				break;

				case 4:
					if (arr[n] & G) printf(HBAR);
					else printf(NOHBAR);
				break;

				case 5:
				case 6:
				case 7:
					if (arr[n] & E) printf(VLBAR);
					else printf(NOVLBAR);
					if (arr[n] & C) printf(VRBAR);
					else printf(NOVRBAR);
				break;

				case 8:
					if (arr[n] & D) printf(HBAR);
					else printf(NOHBAR);
				break;

			}
		}
		printf("\n");
	}
}


