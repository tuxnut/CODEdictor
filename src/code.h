#ifndef _CODE_H_
#define _CODE_H_

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define CODE_VERSION "0.0.1"
#define CTRL_KEY(k) ((k) & 0x1f)
#define ABUF_INIT {NULL, 0}

enum editorKey { ARROW_LEFT = 1000, ARROW_RIGHT, ARROW_UP, ARROW_DOWN };

typedef struct appendBuffer {
	char * b;
	int len;
} t_abuf;

typedef struct editorConfig {
	int cx, cy;
	int s_rows;
	int s_cols;
	struct termios orig_termios;
} t_editorConfig;

t_editorConfig conf;

/* life cycle */
void init();
void enable_raw_mode();
void disable_raw_mode();
void die(const char * msg);

/* editor input */
int read_key();
void process_keypress();
void move_cursor(int key);

/* editor output */
void refresh_screen();
void draw_rows();

/* window manager */
int get_window_size(int * rows, int * cols);
int get_cursor_position(int * rows, int * cols);

/* buffer manager */
void abuf_append(t_abuf * ab, const char * s, int len);
void abuf_free(t_abuf * ab);

#endif /* _CODE_H_ */
