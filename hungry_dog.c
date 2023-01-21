#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

// COMPILE COMMAND: gcc -o hungry_dog hungry_dog.c -lcurses
// RUN COMMAND: ./hungry_dog

int main()
{
	initscr();
	noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // initialize first pair colors
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    init_pair(3, COLOR_CYAN, COLOR_BLUE);
    refresh();

	char mas[10][21];

	// coordenates
	int x = 10;
	int y = 5;

	int ox, oy;
	char key;
	int i;
	//refresh();
	//noecho();

	// we generate a new random position for a new apple, initializing it
	//srand(56);
	srand(time(NULL));

	// apples for dog
	int ax = 5, ay = 3;

	unsigned int eaten_apples = 0;

	do
	{
		//cbreak();
		sprintf(mas[0], "####################");
		for (i = 1; i < 9; i++) // remove the 0 and 9 characters
		{
			sprintf(mas[i], "#                  #");
		}

		sprintf(mas[9], "####################");

		// simulate wall
		if (mas[y][x] == '#')
		{
			x = ox;
			y = oy;
		}

		mas[y][x] = '@'; // dog player
		mas[ay][ax] = '*'; // apples for feed the dog

		//system("cls||clear");
		clear(); // curses clear

		attron(COLOR_PAIR(2));
		mvprintw(LINES - 3, 0, "          APPLES EATEN: %d          ", eaten_apples);
		attroff(COLOR_PAIR(2));

		attron(COLOR_PAIR(1));
		mvprintw(LINES - 2, 0, "             CONTROLS:             ");
		mvprintw(LINES - 1, 0, " W=up S=down A=left D=right E=exit ");
		attroff(COLOR_PAIR(1));

		//printw("This should be printed in black with a red background!\n");

		for (i = 0; i < 10; i++)
		{
			//printf("%s\n", mas[i]);
			attron(COLOR_PAIR(3));
			mvprintw(i, 0, mas[i]);
			attroff(COLOR_PAIR(3));
		}

		//if (!initscr)
		//{
		//	initscr();
		//}

		key = getch();

		ox = x;
		oy = y;

		if (key == 'w') y--;
		if (key == 's') y++;
		if (key == 'a') x--;
		if (key == 'd') x++;

		// if an apple is eaten
		if ((x == ax) && (y == ay))
		{
			eaten_apples++;

			// rand() generates from 0 to RAND_MAX
			ax = rand() * 1.0 / RAND_MAX * 18 + 1;
			ay = rand() * 1.0 /RAND_MAX * 8 + 1;
		}

		refresh();
	}
	while (key != 'e');

	endwin();

	return 0;
}
