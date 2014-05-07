#include <ncurses.h>
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

static void handle_line_fake(char* line) {
	if (line != NULL) {
		if (prog_running) {
			rl_set_prompt(prompt);
			rl_already_prompted = 1;
		}
		return;
	}
	prog_running = 0;

	rl_set_prompt("");
	rl_replace_line("", 0);
	rl_redisplay();
	rl_set_prompt(prompt);
}

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
	clrtoeol();
	wrefresh(winCommandMode);

	/* force readline to think that the current line was "eaten" and executed */
	rl_done = 1;
	return 0;
}

static void install_line_handler() {
	if (rl_bind_key(RETURN, io_handle_enter)) {
		io_printfln("failed to bind RETURN");
		abort();
	}
	rl_callback_handler_install(prompt, handle_line_fake);
}

static void remove_line_handler() {
	rl_unbind_key(RETURN);
	rl_callback_handler_remove();
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


    void handle_line(char* ch) {
        //printf("%s\n", ch);
        add_history(ch);
    }

rl_redisplay_mod() {
	char *line = NULL;
	line = rl_copy_text(0, rl_end);
	rl_replace_line("",0);
	// exec
	
	// reset
	//printf(line);
	// TODO - add prompt to redisplay
	wprintw(winCommandMode, line);
	wrefresh(winCommandMode);
	rl_redisplay();
	refresh();
}
void displayCmdLine(WINDOW *win){
	winCommandMode = win;
	wmove (win, 1, 8);
	//wprintw(win, "<<<");
	wrefresh(win);
        //printf("Start.\n");
	rl_bind_key(RETURN, io_handle_enter);
	rl_redisplay_function = (rl_voidfunc_t*)rl_redisplay_mod;
        rl_callback_handler_install(prompt, handle_line);

        while (prog_running) {
            usleep(10);
            rl_callback_read_char();
        }
        rl_callback_handler_remove();
} 

