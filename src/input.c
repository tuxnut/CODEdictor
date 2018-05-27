#include "code.h"

int read_key()
{
	int nread;
	char c;
	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
	{
		if (nread == -1 && errno != EAGAIN) die("read");
	}
	
	if (c == '\x1b') 
	{
		char seq[3];

		if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
		if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

		if (seq[0] == '[')
		{
			switch (seq[1])
			{
				case 'A': return ARROW_UP;
				case 'B': return ARROW_DOWN;
				case 'C': return ARROW_RIGHT;
				case 'D': return ARROW_LEFT;
			}
		}

		return '\x1b';
	}
	else
	{
		return c;
	}
}

void process_keypress()
{
	int c = read_key();
	
	switch (c)
	{
		/* Exit */
		case CTRL_KEY('q'):
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;
		
		/* move the cursor */
		case ARROW_UP:
		case ARROW_LEFT:
		case ARROW_DOWN:
		case ARROW_RIGHT:
			move_cursor(c);
			break;
	}
}

void move_cursor(int key)
{
	switch (key)
	{
		case ARROW_UP:
			if (conf.cy != 0)
				conf.cy--;
			break;
		case ARROW_LEFT:
			if (conf.cx != 0)
				conf.cx--;
			break;
		case ARROW_DOWN:
			if (conf.cy < conf.s_rows - 1)
				conf.cy++;
			break;
		case ARROW_RIGHT:
			if (conf.cx < conf.s_cols -1)
				conf.cx++;
			break;
	}
}
