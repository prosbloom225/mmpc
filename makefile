CC=gcc
CFLAGS=-g -c -Wall -Wint-conversion
LDFLAGS= -lncurses -lpanel -lreadline -lmpdclient
SOURCES= client.c commandMode.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= mmpc

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm *.o mmpc
