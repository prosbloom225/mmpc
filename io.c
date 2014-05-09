#include <ncurses.h>
#include <panel.h>
#include "io.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/select.h>


WINDOW *winCommandMode;
static char* prompt = ">";
static int prog_running = 1;


int io_handle_enter(int x, int y) {
	char* line = NULL;

	line = rl_copy_text(0, rl_end);
	rl_set_prompt("");
	rl_replace_line("", 1);
	rl_redisplay();

	//cmd_execute(line);

	if (strcmp(line, "") != 0) {
		add_history(line);
	}
	free(line);

	/* rl_set_prompt(prompt); */
	/* rl_redisplay(); */


	// wip - clear line on enter
	wmove(winCommandMode, 1, 1);
	//wprintw(winCommandMode, "      ");
	wclrtoeol(winCommandMode);
	wmove(winCommandMode, 1, 1);
	wprintw(winCommandMode, ">");
	wrefresh(winCommandMode);

	/* force readline to think that the current line was "eaten" and executed */
	rl_done = 1;
	return 0;
}
int io_handle_bs(int x, int y) {
	wprintw(winCommandMode, "<BS>");
	wrefresh(winCommandMode);
	return 0;
}


void io_prompt_set(char *prompt) {
	rl_set_prompt(prompt);
	rl_redisplay();
}

const char* io_prompt_get() {
	return prompt;
}

void io_set_prompt(char* newPrompt) {
	if (newPrompt == NULL) {
		free(newPrompt);
	}
	if (prog_running) {
		rl_set_prompt(newPrompt);
	} else {
		rl_set_prompt("");
	}
	rl_redisplay();
}

int io_message(char* msg)
{
	wclrtoeol(winCommandMode);
	wmove(winCommandMode, 1, 1);
	wprintw(winCommandMode, msg);
	wrefresh(winCommandMode);
	// Pause
	getch();
	return 0;
}

void handle_line(char* ch) {
	//printf("%s\n", ch);
	add_history(ch);
}

void rl_redisplay_mod() {
	/* char *line = NULL; */
	/* // grab last char and redisplay */
	/* line = rl_copy_text(rl_end, rl_end-1); */
	/* wprintw(winCommandMode, line); */
	/* wrefresh(winCommandMode); */
	/* rl_redisplay(); */
	/* refresh(); */

	char *line = NULL;
	line = rl_copy_text(0, rl_end);
	wmove(winCommandMode, 1, 2);
	wclrtoeol(winCommandMode);
	wprintw(winCommandMode, line);
	wrefresh(winCommandMode);
	rl_redisplay();
	refresh();
}

char* displayCmdLine(WINDOW *win){
	curs_set(2);
	winCommandMode = win;
	wmove (win, 1, 1);
	//wprintw(winCommandMode, prompt);
	wrefresh(win);

	//rl_bind_key(RETURN, io_handle_enter);
	rl_redisplay_function = (rl_voidfunc_t*)rl_redisplay_mod;

	wprintw(winCommandMode, prompt);
	char* line = readline(prompt);
	add_history(line);
	// for testing history
	//line = readline(prompt);
	wmove (win, 1, 11);
	wprintw(winCommandMode, line);
	wrefresh(win);
	return line;


	rl_callback_handler_install(prompt, handle_line);

	while (prog_running) {
		usleep(10);
		rl_callback_read_char();
	}
	rl_callback_handler_remove();
	handle_command(rl_line_buffer);
	return rl_line_buffer;
} 

