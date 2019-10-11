/*
# _____     ___   __      ___ ____
#  ____|   |        |    |        | |____|
# |     ___|     ___| ___|    ____| |    \
#-----------------------------------------------------------------------
#
# ANSI C "stdio.h" for PS1.
#
*/

#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUFSIZ 1024
#define EOF (-1)

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

#ifndef SEEK_END
#define SEEK_END 2
#endif

int open(const char*, uint32_t);
int close(int);
int lseek(int, int, int);
int read(int, void*, int);
int write(int, const void*, int);
int ioctl(int, int, int);

int remove(const char* path);
int undelete(const char* path);
int format(const char* path);
int rename(const char* oldname, const char* newname);

int printf(const char* fmt, ...);
int sprintf(char* buffer, const char* fmt, ...);

char getc(int);
char getchar(void);
char* gets(char*);
void putc(char, int);
void putchar(char);
void puts(const char*);

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H */