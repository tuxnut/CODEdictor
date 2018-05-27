#include "code.h"

void enable_raw_mode()
{	
	if (tcgetattr(STDIN_FILENO, &conf.orig_termios) == -1) die("tcgetattr");
	
	atexit(disable_raw_mode);
	
	struct termios raw = conf.orig_termios;
	/* OPOST dor canceling carriage return */
	raw.c_oflag &= ~(OPOST);
	/* IXON for ctrl-C cancel 
	 * ICRNL for crrl-M cancel */
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	/* ECHO for output display
	 * ICANON for reading 1 byte at a time
	 * ISIG for ctrl-C and ctrl-Z cancel 
	 * IEXTEN for ctrl-V cancel */
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	raw.c_cflag |= (CS8);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void disable_raw_mode()
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &conf.orig_termios) == -1) die("tcsetattr");
}
