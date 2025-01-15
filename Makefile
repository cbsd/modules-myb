all: getch checktty

getch: src/getch.c
	cc src/getch.c -o getch && strip getch

checktty: src/checktty.c
	cc src/checktty.c -o checktty && strip checktty

clean:
	rm -f getch checktty *.core
