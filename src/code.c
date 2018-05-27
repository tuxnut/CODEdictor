#include "code.h"

int main(/*int argc, char ** argv*/)
{
	enable_raw_mode();
	init();
	
	while (1)
	{
		refresh_screen();
		process_keypress();
	}
	
	return 0;
}

void init()
{
	conf.cx = 0;
	conf.cy = 0;
	
	if (get_window_size(&conf.s_rows, &conf.s_cols) == -1) die("get_window_size");
}

void die(const char * msg)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	
	perror(msg);
	exit(1);
}
