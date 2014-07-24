#ifndef STRINGHELP_H
#define STRINGHELP_H

#include <string.h>
#include <wchar.h>

void strtowcs(char *,wchar_t *);
int cutrightwcs2(wchar_t *,wchar_t);
char *strcpyn(char *,const char *,int);
int strcmpmin(const char *,const char *);

#endif
