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
int rows, cols;
void cb_linehandler(char* line);

void openCommandMode(WINDOW *window) {
	//keypad(stdscr, true);
	getmaxyx(stdscr, rows, cols);
	move(rows-1,1);
	refresh();
	//rl_prep_terminal(1);
	//rl_callback_handler_install(">", (rl_vcpfunc_t*) &cb_linehandler); 
	//install_line_handler();

	//rl_callback_handler_install(">", cb_linehandler);
	running =1;
	while (!running)
	{
		usleep(1000);
		rl_callback_read_char();
		//printf(rl_line_buffer);
		/* wmove(window, rows-1, 1); */ 
		/* wrefresh(window); */
	}
	//remove_line_handler();
}

void cb_linehandler (char *line) {
	/* rl_done=1; */
	/* rl_set_prompt(">"); */
	/* rl_redisplay(); */
	/* return; */
  if (line == NULL || strcmp (line, "exit") == 0)
  /* Can use ^D (stty eof) or `exit' to exit. */
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
  	
      move(rows-3, 7);
      refresh();
}

