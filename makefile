all:
	gcc -g -o mmpc client.c /usr/local/lib/libmpdclient.a -lncurses -lpanel -lreadline /usr/local/lib/libreadline.a
clean:
	rm *.exe
