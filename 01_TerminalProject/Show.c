#include <curses.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define DX 7
#define DY 3

int main(int argc, char *argv[]) {
	WINDOW *frame, *win;
	FILE * fp;
	int c = 0;
	if (argc < 2)
		return 1;
	fp = fopen( argv[1], "r" );
	if (fp == 0)
		return 1;

	setlocale(LC_ALL, "");
	initscr();
	noecho();
	cbreak();
	printw("Имя файла - %s", argv[1]);
	refresh();
	// test long line ___________________________________________________________________________________________________________________________________________________________________________________________________________
	frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
	box(frame, 0, 0);
	//mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), "Исходный код");
	wrefresh(frame);
	win = newwin(LINES - 2*DY - 2, COLS - 2*DX-2, DY+1, DX+1);
	keypad(win, TRUE);
	scrollok (win, TRUE);

	size_t len = COLS - DX - 4;
	char * line = NULL;

	for (int i = 0; i < LINES - 2 *  DY - 3; i++){
		if (getline(&line, &len, fp) != -1){
			wprintw(win, "%s", line);
			wrefresh(win);
		}
	}

	while((c = wgetch(win)) != 27){
		// wprintw(win, "\n%d: %s", c, keyname(c));
		if (c == 32 && getline(&line, &len, fp) != -1){
                        wprintw(win, "%s", line);
                        wrefresh(win);
                }
	}
	delwin(win);
	delwin(frame);
	endwin();
	return 0;
}
