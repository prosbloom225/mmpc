CC=gcc
CFLAGS=-g -c -Wall 
LDFLAGS= -lncurses -lpanel -lreadline -lmpdclient /usr/local/lib/libreadline.a
SOURCES= client.c commandMode.c io.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= mmpc

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm *.o mmpc
