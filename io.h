#ifndef __XC_IO_H__
#define __XC_IO_H__

#include <stdbool.h>

void io_init();
void io_deinit();
void io_switch_debug();
void io_nonblock_handle();
void io_debug_set(bool st);
bool io_debug_get();

void io_prompt_set(char *prompt);
const char* io_prompt_get();

void io_notification(const char* const fmt, ...);
void io_error(const char* const fmt, ...);
void io_message(const char* msg);
void io_debug(const char * const fmt, ...);
void io_printfln(const char* const fmt, ...);

char* io_getpass();
char* rlread();
#endif
