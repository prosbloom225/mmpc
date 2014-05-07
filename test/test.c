#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/select.h>


    const* prompt = ">";
    int running = 1;

    void printlog(int c) {
        char* saved_line;
        int saved_point;
        saved_point = rl_point;
        saved_line = rl_copy_text(0, rl_end);
        rl_set_prompt("");
        rl_replace_line("", 0);
        rl_redisplay();
        //printf("Message: %d\n", c);
        rl_set_prompt(prompt);
        rl_replace_line(saved_line, 0);
        rl_point = saved_point;
        rl_redisplay();
        free(saved_line);
    }

    void handle_line(char* ch) {
        //printf("%s\n", ch);
        add_history(ch);
    }

int io_handle_enter(int x, int y) {
	char* line = NULL;

	line = rl_copy_text(0, rl_end);
	rl_set_prompt("");
	rl_replace_line("", 0);
	rl_redisplay();

	//cmd_execute(line);

	if (strcmp(line, "") != 0) {
		add_history(line);
	}
	free(line);

	//rl_set_prompt(prompt);
	rl_redisplay();

	/* force readline to think that the current line was "eaten" and executed */
	rl_done = 1;
	return 0;
}

    int main() {

        printf("Start.\n");
	rl_bind_key(RETURN, io_handle_enter);
        rl_callback_handler_install(prompt, handle_line);

        while (running) {
            usleep(10);
            rl_callback_read_char();
        }
        rl_callback_handler_remove();
    }
