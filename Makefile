
exec:
	@make all
	balls
all:
	@g++ -I/usr/X11/include -c main.c
	@g++ -L/usr/X11/lib main.o -lXaw -lXt -lXmu -lX11 -lm -o balls
	@cp ./balls /usr/local/bin/

install:
	@cp ./balls /usr/local/bin/
