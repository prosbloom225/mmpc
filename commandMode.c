/*
 * =====================================================================================
 *
 *       Filename:  commandMode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2014 20:08:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>

#include "commandMode.h"

int running;

void openCommandMode(WINDOW *window)
{
	keypad(stdscr, true);
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	printf("%d", rows);
	wmove (window, rows-1, 1);
	wrefresh(window);
//	rl_prep_terminal(1);
	rl_callback_handler_install(">", (rl_vcpfunc_t*) &cb_linehandler);
	running =1;
	while (running)
	{
		usleep(1000);
		rl_callback_read_char();
		wmove(window, rows-1, 1);
		wrefresh(window);
	}
	rl_callback_handler_remove();
}

void cb_linehandler (char *line) {
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
      free (line);
    }
}
