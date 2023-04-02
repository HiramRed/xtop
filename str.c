#include "str.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int
str_last_index_of(char *src, unsigned char ch)
{
    assert(src != NULL);

    if (src == NULL) return -1;
    int len = strlen(src);
    for (int i = len - 1; i >= 0; i--)
        if (src[i] == ch) return i;
    return -1;
}

char*
str_slice(char *src, size_t begin, size_t n)
{
    assert(src != NULL);
    assert((long)begin >= 0);
    assert((long)n >= 0);

    char *dst = malloc(sizeof(char) * n);
    memcpy(dst, src + begin, n);
    return dst;
}

