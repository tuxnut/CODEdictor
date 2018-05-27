#include "code.h"

void abuf_append(t_abuf * ab, const char * s, int len)
{
	char * new = (char*)realloc(ab->b, ab->len + len);
	
	if (new == NULL) return;
	memcpy(&new[ab->len], s, len);
	ab->b = new;
	ab->len += len;
}

void abuf_free(t_abuf * ab)
{
	free(ab->b);
}
