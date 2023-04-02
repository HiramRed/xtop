#ifndef __STR_H__
#define __STR_H__

#define EMPTY_STR malloc(0)

#include <sys/_types/_size_t.h>

/* find the last index of 'character', return -1 if not finded */
int str_last_index_of(char *src, unsigned char ch);

/* create and return a new content from the source string */
char* str_slice(char *src, size_t begin, size_t n);

#endif
