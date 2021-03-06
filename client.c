/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  05/05/2014 20:01:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michael Osiecki
 *   Organization:  
 *
 * =====================================================================================
 */


#include <ncurses.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <panel.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpd/client.h>
#include <string.h>

#include "io.h"

#define Nrows 10
#define NCOLS 40

// HEADER
void printToWindow(WINDOW *win, int starty, int startx, int width, char *string, chtype color); 	
// END HEADER


// DATA SEGMENT
WINDOW *clientWins[3];
PANEL  *clientPanels[3];
WINDOW *winCommandMode;
PANEL *panelCommandMode;
int rows, cols, x = 0, y = 0;
int running;
const char *prompt = "rltest$ ";


struct mpd_connection * conn;
// END DATA SEGMENT

int main() {
	initscr();
	getmaxyx(stdscr,rows,cols);
	cbreak();
	//noecho();

	clientWins[0] = newwin(rows/4, cols-2, y, x);
	clientWins[1] = newwin(((rows/4)*3)-2, (cols-2)/3, y + (rows/4), x);
	clientWins[2] = newwin(((rows/4)*3)-2, ((cols-2)/3)*2, y + (rows/4), x + (cols-2)/3);
	winCommandMode = newwin(rows, cols, rows-2, 0);
	// Create panels
	clientPanels[0] = new_panel(clientWins[0]);
	clientPanels[1] = new_panel(clientWins[1]);
	clientPanels[2] = new_panel(clientWins[2]);
	panelCommandMode = new_panel(winCommandMode);

	// Prettify
	box(clientWins[0], 0, 0);
	box(clientWins[1], 0, 0);
	box(clientWins[2], 0, 0);
	//box(winCommandMode, 0, 0);


	update_panels();
	doupdate();

	printToWindow(clientWins[0], 0, 0, 20, "Viz", COLOR_PAIR(1));
	printToWindow(clientWins[1], 0, 0, 20, "Library", COLOR_PAIR(1));
	printToWindow(clientWins[2], 0, 0, 20, "Playlist", COLOR_PAIR(1));
	//printToWindow(winCommandMode, 0, 0, 20, "CMD", COLOR_PAIR(1));

	displayCmdLine(winCommandMode);

	//connectToMpd("localhost", 6600, 0);

	// Pause
	getch();
	endwin();
	return 0;
}


void printToWindow(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {	
	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	update_panels();
	refresh();
}

