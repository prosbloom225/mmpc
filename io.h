/*
 * =====================================================================================
 *
 *       Filename:  io.h
 *
 *    Description:  Header for io. Handles io interface
 *
 *        Version:  1.0
 *        Created:  05/05/2014 20:03:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Michael Osiecki
 *
 * =====================================================================================
 */
#ifndef IO_H
#define IO_H

#include <ncurses.h>

void io_prompt_set(char *prompt);
const char* io_prompt_get();
int io_handle_enter(int x, int y);
void io_set_prompt(char* prompt);

int io_message (char *msg);

void handle_line(char* ch);
void rl_redisplay_mod();
char* displayCmdLine(WINDOW *win);


#endif
