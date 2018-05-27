#include "code.h"

void refresh_screen()
{
	t_abuf ab = ABUF_INIT;
	
	/* hide cursor */
	abuf_append(&ab, "\x1b[?25l", 6);
	/* place the cursor at the top-left */
	abuf_append(&ab, "\x1b[H", 3);
	
	draw_rows(&ab);
	
	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", conf.cy + 1, conf.cx + 1);
	abuf_append(&ab, buf, strlen(buf));
	
	/* display the cursor */
	abuf_append(&ab, "\x1b[?25h", 6);
	
	write(STDOUT_FILENO, ab.b, ab.len);
	abuf_free(&ab);
}

void draw_rows(t_abuf * ab)
{
	for (int i = 0; i < conf.s_rows; ++i)
	{
		/* On the 3rd row */
		if (i == conf.s_rows / 3)
		{
			/* init the welcome (version) msg */
			char welcome[80];
			int len_welcome = snprintf(welcome, sizeof(welcome), "code editor -- v%s", CODE_VERSION);
			
			/* crop msg if too large */
			if (len_welcome > conf.s_cols) len_welcome = conf.s_cols;
			
			/* center it */
			int padding = (conf.s_cols - len_welcome) / 2;
			if (padding)
			{
				abuf_append(ab, "~", 1);
				padding--;
			}
			while (padding--) abuf_append(ab, " ", 1);
			
			abuf_append(ab, welcome, len_welcome);
		}
		else
		{
			abuf_append(ab, "~", 1);
		}

		/* Erase line from the right of the cursor */
		abuf_append(ab, "\x1b[K", 3);
		
		if (i < conf.s_rows - 1)
		{
			abuf_append(ab, "\r\n", 2);
		}
	}
}
