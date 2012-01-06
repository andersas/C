#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
int right[4], guess[4], backup[4];
int halfrights,rights;
int tmp,i;
int tries = 3;
int maxtries;
int place,color;
int x,y;
char charbuffer[10];
char question[2];
int pplace[4];
pplace[0] = 13;
pplace[1] = 15;
pplace[2] = 17;
pplace[3] = 19;

halfrights=rights=0;

srand(time(0));

printf("Can two places be the same color? (y/n) ");
scanf("%s",charbuffer);
strcpy(question,"n");
if (strcmp(charbuffer,question) == 0) {
	for (i=0;i<4;i++) {
		BACK:
		right[i] = (8.0*rand()/RAND_MAX+1.0);
		for (tmp=0;tmp<4;tmp++) {
			if (right[i] == right[tmp] && i != tmp) {
				goto BACK;
			}
		}
		guess[i] = 0;
	}
} else {
	for (i=0;i<4;i++) {
		right[i] = (8.0*rand()/RAND_MAX+1.0);
		guess[i] = 0;
	}
}


for (i=0;i<4;i++) {
	backup[i] = right[i];
}

printf("How many tries would you like? ");
scanf("%i",&maxtries);
printf("\n");
if (maxtries <= 0) {
printf("Ok, fine.\n");
return 1;
}

printf("\nI have come up with a color combination. Press enter to start the game.\n");

getchar();
getchar();

initscr();
start_color();

getmaxyx(stdscr,y,x);

if (y < 22) {
	endwin();
	printf("Terminal too small\n");
	return 1;
}

if (maxtries > (x/3-3)) {
endwin();
printf("You have too many tries to be on the screen.\n");
return 1;
}

/* Color definations: */
init_pair(1, COLOR_WHITE, COLOR_RED);
init_pair(2, COLOR_WHITE, COLOR_GREEN);
init_pair(3, COLOR_WHITE, COLOR_BLUE);
init_pair(4, COLOR_WHITE, COLOR_BLACK);
init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
init_pair(6, COLOR_BLACK, COLOR_WHITE);
init_pair(7, COLOR_WHITE, COLOR_CYAN);
init_pair(8, COLOR_WHITE, COLOR_YELLOW);


mvprintw(5,0,"Colors: 1: Red, 2: Green, 3: Blue, 4: Black");
mvprintw(6,0,"Colors: 5: Magenta, 6: White, 7: Cyan, 8: Yellow");

mvprintw(8,0,"Right colors on right places:");
mvprintw(10,0,"Right colors on wrong places:");

mvprintw(pplace[0],0,"1:");
mvprintw(pplace[1],0,"2:");
mvprintw(pplace[2],0,"3:");
mvprintw(pplace[3],0,"4:");

mvprintw(0,x/2-10,"Tries left: %i ",maxtries);

GETPLACE:
mvprintw(0,0,"Place:");
mvprintw(1,2," ");
mvprintw(1,0,"? ");
scanw("%i",&place);
if (place < 1 || place > 4) { /* if the user types too many */
	for (i=2;i<=x;i++) {  /* cifers, we want to clean it up */
	mvprintw(1,i," ");
	}
goto GETPLACE;
}
GETCOLOR:
mvprintw(0,0,"Color:");
mvprintw(1,2," ");
move(1,2);
scanw("%i",&color);
if (color < 1 || color > 8) { /* same here */
	for (i=2;i<=x;i++) {
	mvprintw(1,i," ");
	}
goto GETCOLOR;
}

attrset(COLOR_PAIR(color));

mvprintw(pplace[place-1],tries,"%i",color);

attrset(A_NORMAL);

guess[place-1] = color;

tmp = 1;
for (i=0;i<4;i++) {
	if (guess[i] == 0) {
	tmp = 0;	
	}
}

if (tmp) { /* All fields are filled */
	mvprintw(pplace[3]+2,4,"Is that a guess? (y/n) ");
	refresh();
	scanw("%s",charbuffer);
	strcpy(question,"y");
	for (i=4;i<=x;i++) {
		mvprintw(pplace[3]+2,i," ");
	}

	if (strcmp(charbuffer,question) == 0) {
		for (i=0;i<4;i++) {
			if (right[i] == guess[i]) {  /* Finds out how many right colors on right places */
				rights++;	     /* the user has placed. */
				right[i] = guess[i] = 0; /* This line makes sure this guess is not counted again */
			}
		}
		for (i=0;i<4;i++) {
			for (tmp=0;tmp<4;tmp++) {

				if (guess[tmp] == right[i] && right[i] != 0) {
					halfrights++;
					guess[tmp] = right[i] = 0; /* This line makes sure this guess is not counted again */
				}

			}
		}

		if (rights == 4) {
			endwin();
			printf("CONGRATULATIONS!\n");
			printf("You guessed the right combination!\n");
			printf("You used %i tries\n", tries/3);

			return 0;
		}
	
		for (i=0;i<4;i++) {
			right[i] = backup[i];  /* We deleted the right[] array, we have to get it back for next check */
		}


		mvprintw(9,tries,"%i",rights);
		mvprintw(11,tries,"%i",halfrights);
		

		halfrights=rights=0;
		for (i=0;i<4;i++) {
			guess[i] = 0;
		}
		tries = tries+3;
		maxtries--;
		mvprintw(0,x/2-10,"Tries left: %i ",maxtries);
		if (maxtries == 0) {
			for (i=0;i<4;i++) {
				attrset(COLOR_PAIR(right[i]));

				mvprintw(pplace[i],0,"%i",right[i]);

				attrset(A_NORMAL);

			}
			mvprintw(y-2,0,"Wrong, and you are out of tries..\n");
			printw("Press enter to end program");
			refresh();
			getchar();
			endwin();
			return 1;
		}
	}
}


goto GETPLACE;

endwin();
return 0;
}
