CC=gcc
CFLAGS=-g -c -Wall 
LDFLAGS= -lncurses -lpanel -lreadline -lmpdclient /usr/local/lib/libreadline.a
SOURCES= client.c commandMode.c io.c \
	mpc/list.c mpc/list.h \
	mpc/password.c mpc/password.h mpc/status.c mpc/status.h \
	mpc/args.c mpc/args.h mpc/util.c mpc/util.h mpc/command.c \
	mpc/command.h mpc/queue.c mpc/queue.h mpc/sticker.c \
	mpc/sticker.h mpc/tab.c mpc/tab.h mpc/idle.c mpc/idle.h \
	mpc/message.c mpc/message.h mpc/search.c mpc/search.h \
	mpc/options.c mpc/options.h mpc/path.c mpc/path.h \
	mpc/Compiler.h mpc/charset.c mpc/charset.h
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= mmpc

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm *.o mmpc
