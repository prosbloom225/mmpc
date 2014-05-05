#include <ncurses.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <panel.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpd/client.h>
#include <string.h>

#define Nrows 10
#define NCOLS 40

// HEADER
void printToWindow(WINDOW *win, int starty, int startx, int width, char *string, chtype color); 	
int connectToMpd(); 
// END HEADER


// DATA SEGMENT
	WINDOW *clientWins[3];
	PANEL  *clientPanels[3];
	int rows, cols, x = 0, y = 0;
	static void cb_linehandler (char *);
	int running;
	const char *prompt = "rltest$ ";
// END DATA SEGMENT
static void
cb_linehandler (char *line) {
  /* Can use ^D (stty eof) or `exit' to exit. */
  if (line == NULL || strcmp (line, "exit") == 0)
    {
      if (line == 0)
        printf ("\n");
      printf ("exit\n");
      /* This function needs to be called to reset the terminal settings,
         and calling it from the line handler keeps one extra prompt from
         being displayed. */
      rl_callback_handler_remove ();

      running = 0;
    }
  else
    {
      if (*line)
        add_history (line);
      //printf ("input line: %s\n", line);
      printToWindow(clientWins[0], 1, 1, 20, line, COLOR_PAIR(1));
      free (line);
    }
}

int main() {

	initscr();
	getmaxyx(stdscr,rows,cols);
	cbreak();
	//noecho();

	clientWins[0] = newwin(rows/4, cols-2, y, x);
	clientWins[1] = newwin((rows/4)*3, (cols-2)/3, y + (rows/4), x);
	clientWins[2] = newwin((rows/4)*3, ((cols-2)/3)*2, y + (rows/4), x + (cols-2)/3);
	
	// Create panels
	clientPanels[0] = new_panel(clientWins[0]);
	clientPanels[1] = new_panel(clientWins[1]);
	clientPanels[2] = new_panel(clientWins[2]);

	// Prettify
	box(clientWins[0], 0, 0);
	box(clientWins[1], 0, 0);
	box(clientWins[2], 0, 0);

	update_panels();
	doupdate();

	printToWindow(clientWins[0], 0, 0, 20, "Viz", COLOR_PAIR(1));
	printToWindow(clientWins[1], 0, 0, 20, "Library", COLOR_PAIR(1));
	printToWindow(clientWins[2], 0, 0, 20, "Playlist", COLOR_PAIR(1));


	//printToWindow(clientWins[0], 1, 1, 20, "test", COLOR_PAIR(1));

	//commandMode();

	
	mvwprintw(clientWins[1], 1, 1, "aTest");
	mvwprintw(clientWins[2], 1, 1, "bTest");
	wrefresh(clientWins[1]);

	keypad(stdscr, true);
	fd_set fds;
	int r;
	rl_callback_handler_install(">", cb_linehandler);

	running = 1;
	while (running)
	{
		FD_ZERO (&fds);
		r = select (FD_SETSIZE, &fds, NULL, NULL, NULL);
		if (r<0)
		{
			perror("rltest: select");
			rl_callback_handler_remove();
			break;
		}
		if (FD_ISSET (fileno (rl_instream), &fds))
		{
			rl_callback_read_char();
			//printToWindow(clientWins[0], 1, 1, 20, "TEST", COLOR_PAIR(1));
		}
	}

	//printToWindow(clientWins[0], 1, 1, 20, rl_line_buffer, COLOR_PAIR(1));


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
int connectToMpd() {
	struct mpd_connection * conn;
	conn = mpd_connection_new ("localhost", 6600, 0);

    if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) 
    {
		mpd_connection_free(conn);
		printf("Connection failed.\n");
    }
    else
    {
	    printf("Connection established.\n");
    }


	printf("End\n");
	return 0;
}
