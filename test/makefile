CC=gcc
CFLAGS=-g -c -Wall 
LDFLAGS= -lncurses -lpanel -lreadline -lmpdclient /usr/local/lib/libreadline.a
SOURCES= test.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= a

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm *.o a
