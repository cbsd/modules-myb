all: getch

getch: src/getch.c
	cc src/getch.c -o getch && strip getch

clean:
	rm -f getch *.core
