CC=gcc
CFLAGS=-g -c -Wall 
LDFLAGS= -lncurses -lpanel -lreadline -lmpdclient /usr/local/lib/libreadline.a
SOURCES= client.c io.c mpdControl.c command.c status.c util.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= mmpc

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm *.o mmpc
