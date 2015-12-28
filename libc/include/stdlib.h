#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

__attribute__((__noreturn__)) void abort(void);
__attribute__((__noreturn__)) void exit(int);
int atexit(void (*)(void));
int atoi(const char *);
void free(void *);
char *getenv(const char *);
void *malloc(size_t);

#endif
