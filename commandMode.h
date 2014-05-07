/*
 * =====================================================================================
 *
 *       Filename:  commandMode.h
 *
 *    Description:  Header for command mode.  Impements readline to build a vi-like
 *    command line implementation.
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
#include <ncurses.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>



#ifndef CMDLINE_H
#define CMDLINE_H
int running;

void cb_linehandler (char *line);
void openCommandMode(WINDOW *window);
#endif

