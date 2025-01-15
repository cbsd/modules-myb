// return 0 when terminal size > 28 row/ 83 col  (20x80 default minimal size)
#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

enum FMT { NOTSET, GFLAG, BSD, POSIX };

struct info {
	int fd;                                 /* file descriptor */
	int ldisc;                              /* line discipline */
	int off;                                /* turn off */
	int set;                                /* need set */
	int wset;                               /* need window set */
	const char *arg;                        /* argument */
	struct termios t;                       /* terminal info */
	struct winsize win;                     /* window info */
};

int main (int argc, char **argv)
{
	struct info i;
	enum FMT fmt;
	fmt = NOTSET;
	i.fd = STDIN_FILENO;
	const char *file, *errstr = NULL;
	file = "stdin";

	if (tcgetattr(i.fd, &i.t) < 0)
		exit(1);	// errx(1, "%s isn't a terminal", file);
	if (ioctl(i.fd, TIOCGETD, &i.ldisc) < 0)
		exit(1);	// err(1, "TIOCGETD");
	if (ioctl(i.fd, TIOCGWINSZ, &i.win) < 0)
		exit(1);	// warn("TIOCGWINSZ");

	//printf("row %d; col %d\n",i.win.ws_row,i.win.ws_col);

	// >24 +>80
	if ((i.win.ws_row<28)||(i.win.ws_col<83))
		exit(1);

	exit(0);
}
